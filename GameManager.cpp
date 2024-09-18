#include "GameManager.h"

#include "System.h"
#include "Input.h"
#include "Map.h"
#include "Chest.h"
#include "Character.h"


const char *GameManager::defaultMaps[]
{
    "Map.txt",
    "Map2.txt",
};


GameManager::GameManager()
{

}

void GameManager::run()
{
    currentMap = 0;

    loadMap();

    while (1)
    {
        playerActionMove();

        enemyAction();

        if (Map::getInstance().getPlayer()->isDead()) {
            loadMap();
        }
    }
}


void GameManager::notifyEnemyAttack(Entity *attacker, Entity *target)
{
    renderer.clearPlayerRegion();
    renderer.drawMessage(attacker->name + " attacked you!");
    waitForEnter();

    int damage = attacker->attack(target);

    renderer.clearPlayerRegion();
    renderer.drawMessage(attacker->name + " deals " + std::to_string(damage) + " damage.");
    waitForEnter();
}

void GameManager::loadMap()
{
    Map::getInstance().clear();
    Map::getInstance().load(GameManager::defaultMaps[currentMap]);

    Map &map = Map::getInstance();
    System::getInstance().resizeForGridSize(map.getWidth(), map.getHeight());

    // Setup renderer.
    renderer.setGridSize(map.getWidth(), map.getHeight());
    renderer.clearEnemyRegion();
    renderer.clearPlayerRegion();
}

void GameManager::redrawAll()
{
    Map &map = Map::getInstance();

    // Redraw grid (forces contents to be cleared & redrawn).
    renderer.drawGrid();

    // Draw entities.
    Character *p = map.getPlayer();
    renderer.drawEntity(p->getIcon(), p->getPosX(), p->getPosY());

    for (Entity *e : map.getEnemies())
    {
        renderer.drawEntity(e->getIcon(), e->getPosX(), e->getPosY());
    }
    for (Chest *c : map.getChests())
    {
        renderer.drawEntity('c', c->getPosX(), c->getPosY());
    }

    // Draw stats.
    renderer.clearPlayerRegion();
    renderer.drawPlayerStats(p->name, p->health, p->maxHealth, p->attackDamage, p->defense, p->mana, p->level, p->xp, p->xpToLevelUp);
}

void GameManager::playerActionMove()
{
    Map &map = Map::getInstance();
    Entity *p = map.getPlayer();

    playerRemainingMP = p->getMovementPoint();

    // Player move loop.
    int cursorX = p->getPosX(), cursorY = p->getPosY();
    int newX = cursorX, newY = cursorY;
    bool canMove = true;

    while (playerRemainingMP > 0)
    {
        redrawAll();

        // Check if over object or enemy.
        canMove = !map.isTileOccupied(cursorX, cursorY);
        uint16_t cursorColor = canMove ? 0x2F : 0x4F;

        renderer.drawRange(0x1F, p->getPosX(), p->getPosY(), playerRemainingMP);
        renderer.drawColor(cursorColor, cursorX, cursorY);

        // Draw actions.
        if (!nearbyEnemies.empty()) {
            renderer.drawAction("(A) Attack", 0);
        }
        if (!nearbyChests.empty()) {
            renderer.drawAction("(C) Open chest", 1);
        }

        WORD key = Input::getInstance().waitForInput();

        // Erase.
        renderer.drawColor(0x70, cursorX, cursorY);

        // Listen to action.
        switch (key)
        {
        case VK_UP:    if (newY != 0)                   newY--; break;
        case VK_DOWN:  if (newY != map.getHeight() - 1) newY++; break;
        case VK_LEFT:  if (newX != 0)                   newX--; break;
        case VK_RIGHT: if (newX != map.getWidth() - 1)  newX++; break;
        case VK_SPACE:
            if (canMove) {
                movePlayerTo(cursorX, cursorY);
                updateNearbyEnemyAndChest();
            }
            break;
        case VK_RETURN:
            playerRemainingMP = 0;
            break;
        case 'A':
            if (nearbyEnemies.empty()) break;
            playerActionAttack();
            break;
        case 'C':
            if (nearbyChests.empty()) break;
            playerActionCollect();
            break;
        }

        // Move cursor.
        if (isMoveValid(p, playerRemainingMP, newX, newY)) {
            cursorX = newX;
            cursorY = newY;
        }
        else {
            newX = cursorX;
            newY = cursorY;
        }
    }

    redrawAll();
    updateNearbyEnemyAndChest();
}

void GameManager::playerActionAttack()
{
    Map& map = Map::getInstance();
    Entity* p = map.getPlayer();
    int damage;

    if (nearbyEnemies.empty()) return;

    int enemyIndex = 0;
    bool done = false;
    while (!done)
    {
        Entity* selectedEnemy = nearbyEnemies[enemyIndex];

        renderer.drawRange(0x3F, p->getPosX(), p->getPosY(), 1);
        renderer.drawColor(0x2F, selectedEnemy->getPosX(), selectedEnemy->getPosY());

        if (getDistance(p, selectedEnemy->getPosX(), selectedEnemy->getPosY()) == 1) {
            renderer.drawEnemyStats(selectedEnemy->name, selectedEnemy->health,
                selectedEnemy->getMaxHealth(), selectedEnemy->getAttackDamage(),
                selectedEnemy->getDefense());
        }

        // Draw actions.
        renderer.drawAction("(Left/Right) Select enemy", 0);
        renderer.drawAction("(Enter) Attack", 1);
        renderer.drawAction("(A) Cancel", 2);

        WORD key = Input::getInstance().waitForInput();

        // Listen to action.
        switch (key)
        {
        case VK_LEFT:
            enemyIndex--;
            if (enemyIndex == -1) enemyIndex = nearbyEnemies.size() - 1;
            break;
        case VK_RIGHT:
            enemyIndex++;
            if (enemyIndex == nearbyEnemies.size()) enemyIndex = 0;
            break;
        case VK_RETURN:
            renderer.clearPlayerRegion();
            renderer.drawMessage("You attacked " + selectedEnemy->name + '!');
            waitForEnter();

            damage = p->attack(selectedEnemy);

            renderer.clearEnemyRegion();
            renderer.drawEnemyStats(selectedEnemy->name, selectedEnemy->health,
                selectedEnemy->getMaxHealth(), selectedEnemy->getAttackDamage(),
                selectedEnemy->getDefense());
            renderer.clearPlayerRegion();
            renderer.drawMessage("You dealt " + std::to_string(damage) + " damage.");
            waitForEnter();

            if (selectedEnemy->isDead()) {
                renderer.clearPlayerRegion();
                renderer.drawMessage(selectedEnemy->name + " is dead!");
                waitForEnter();

                killEnemy(selectedEnemy);
            }

            updateNearbyEnemyAndChest();

            // End turn automatically.
            playerRemainingMP = 0;

            done = true;
            break;
        case 'A':
            done = true;
            break;
        }
    }

    renderer.clearEnemyRegion();
}

void GameManager::playerActionCollect()
{
    Map &map = Map::getInstance();
    Character *p = map.getPlayer();

    for (Chest *chest : nearbyChests) {
        p->openChest(chest);

        // TODO : Actually display the chest's loot.
        renderer.clearPlayerRegion();
        renderer.drawMessage("You found a chest with ...!");
        waitForEnter();

        removeChest(chest);
    }
}

void GameManager::enemyAction()
{
    for (Entity *enemy : Map::getInstance().getEnemies())
    {
        enemy->update();
    }

    if (Map::getInstance().getPlayer()->isDead()) {
        renderer.clearPlayerRegion();
        renderer.drawMessage("You are dead! Game over!");
        waitForEnter();
    }
}

void GameManager::updateNearbyEnemyAndChest()
{
    Map& map = Map::getInstance();
    Character* p = map.getPlayer();

    nearbyEnemies.clear();
    nearbyChests.clear();

    for (Entity *enemy : map.getEnemies()) {
        if (getDistance(p, enemy->getPosX(), enemy->getPosY()) == 1) {
            nearbyEnemies.push_back(enemy);
        }
    }

    for (Chest *chest : map.getChests()) {
        if (getDistance(p, chest->getPosX(), chest->getPosY()) == 1) {
            nearbyChests.push_back(chest);
        }
    }
}

void GameManager::movePlayerTo(int x, int y)
{
    Map& map = Map::getInstance();
    Entity* p = map.getPlayer();

    playerRemainingMP -= getDistance(p, x, y);
    p->posX = x;
    p->posY = y;

    updateNearbyEnemyAndChest();
}

void GameManager::moveEnemyTo(Entity* entity, int x, int y)
{
    if (isEnemyMoveValid(entity, x, y))
    {
        entity->posX = x;
        entity->posY = y;
    }
}

void GameManager::killEnemy(Entity *e)
{
    Map::getInstance().removeEnemy(e);
}

void GameManager::removeChest(Chest *c)
{
    Map::getInstance().removeChest(c);
}

void GameManager::waitForEnter()
{
    WORD key;
    do {
        key = Input::getInstance().waitForInput();
    } while (key != VK_RETURN);
}


int GameManager::getDistance(Entity *entity, int x, int y)
{
    return abs(x - entity->getPosX()) + abs(y - entity->getPosY());
}

bool GameManager::isMoveValid(Entity *entity, int mp, int desiredX, int desiredY)
{
    int distance = getDistance(entity, desiredX, desiredY);
    return distance <= mp;
}

bool GameManager::isEnemyMoveValid(Entity* entity, int desiredX, int desiredY)
{
    Map& map = Map::getInstance();
    Character* p = map.getPlayer();

    if (getDistance(entity, desiredX, desiredY) > entity->getMovementPoint()) return false;
    if (map.isTileOccupied(desiredX, desiredY)) return false;
    if (desiredX < 0 || desiredX >= map.getWidth() || desiredY < 0 || desiredY >= map.getHeight()) return false;

    return true;
}
