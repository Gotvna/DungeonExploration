#include "GameManager.h"

#include "System.h"
#include "Input.h"
#include "Map.h"
#include "Chest.h"
#include "Character.h"


GameManager::GameManager()
{

}

void GameManager::run()
{
    loadMap();

    while (1)
    {
        playerActionMove();

        enemyAction();
    }
}

void GameManager::loadMap()
{
    Map::getInstance().clear();
    Map::getInstance().load("Map.txt");

    Map &map = Map::getInstance();
    System::getInstance().resizeForGridSize(map.getWidth(), map.getHeight());

    // Setup renderer.
    renderer.setGridSize(map.getWidth(), map.getHeight());
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
    while (playerRemainingMP > 0)
    {
        redrawAll();

        renderer.drawRange(0x1F, p->getPosX(), p->getPosY(), playerRemainingMP);
        renderer.drawColor(0x2F, cursorX, cursorY);

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
            movePlayerTo(cursorX, cursorY);
            break;
        case VK_RETURN:
            map.getEnemies()[0]->die();
            return;
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
}

void GameManager::playerActionAttack()
{
    Map &map = Map::getInstance();
    Entity *p = map.getPlayer();

    int enemyIndex = 0;
    while (1)
    {
        Entity* selectedEnemy = nearbyEnemies[enemyIndex];

        renderer.drawRange(0x3F, p->getPosX(), p->getPosY(), 1);
        renderer.drawColor(0x2F, selectedEnemy->getPosX(), selectedEnemy->getPosY());

        renderer.drawEnemyStats(selectedEnemy->name, selectedEnemy->health, selectedEnemy->getMaxHealth(), selectedEnemy->getAttackDamage());

        WORD key = Input::getInstance().waitForInput();

        // Listen to action.
        switch (key)
        {
        case VK_LEFT:  enemyIndex--; if (enemyIndex == -1)                   enemyIndex = nearbyEnemies.size() - 1; break;
        case VK_RIGHT: enemyIndex++; if (enemyIndex == nearbyEnemies.size()) enemyIndex = 0;                        break;

        case VK_RETURN:
            break;
        case 'A':
            break;
        }
    }
}

void GameManager::playerActionCollect()
{
    Map &map = Map::getInstance();
    Character *p = map.getPlayer();

    for (Chest *chest : nearbyChests) {
        chest->getLoot();
        
        waitForEnter();
    }
}

void GameManager::enemyAction()
{
    for (Entity *enemy : Map::getInstance().getEnemies())
    {
        enemy->move();
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
