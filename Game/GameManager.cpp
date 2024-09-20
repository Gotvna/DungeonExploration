#include "GameManager.h"

#include "Engine/System.h"
#include "Engine/Input.h"
#include "Game/Map/Map.h"
#include "Game/Map/Chest.h"
#include "Game/Character/Character.h"

#include "Config/Color.h"

#include <iostream>


const char *GameManager::defaultMaps[]
{
    "data/Map.txt",
    "data/Map2.txt",
};


GameManager::GameManager()
{

}

void GameManager::run()
{
    GameManager::getInstance()._run();
}

void GameManager::_run()
{
    m_currentMap = 0;

    reloadMap();

    while (1)
    {
        updateNearbyEnemyAndChest();
        playerActionMove();

        if (checkPlayerWin()) {
            continue;
        }

        enemyAction();

        checkPlayerDeath();
    }
}


void GameManager::notifyEnemyAttack(Entity *attacker, Entity *target)
{
    m_renderer.clearPlayerRegion();
    m_renderer.drawMessage(attacker->name + " attacked you!");
    waitForEnter();

    int damage = attacker->attack(target);

    m_renderer.clearPlayerRegion();
    m_renderer.drawMessage(attacker->name + " deals " + std::to_string(damage) + " damage.");
    waitForEnter();
}

void GameManager::reloadMap()
{
    Map::getInstance().reset();
    Map::getInstance().load(GameManager::defaultMaps[m_currentMap]);

    Map &map = Map::getInstance();
    System::getInstance().resizeForGridSize(map.getWidth(), map.getHeight());

    // Setup renderer.
    m_renderer.setGridSize(map.getWidth(), map.getHeight());
    m_renderer.clearEnemyRegion();
    m_renderer.clearPlayerRegion();
}

void GameManager::loadNextMap()
{
    Map::getInstance().clear();
    Map::getInstance().load(GameManager::defaultMaps[m_currentMap]);

    Map &map = Map::getInstance();
    System::getInstance().resizeForGridSize(map.getWidth(), map.getHeight());

    // Setup renderer.
    m_renderer.setGridSize(map.getWidth(), map.getHeight());
    m_renderer.clearEnemyRegion();
    m_renderer.clearPlayerRegion();
}

void GameManager::redrawAll()
{
    Map &map = Map::getInstance();

    // Redraw grid (forces contents to be cleared & redrawn).
    m_renderer.drawGrid(COLOR_GRID, COLOR_WALL, map.getWalls());

    // Draw entities.
    Character *p = map.getPlayer();
    m_renderer.drawEntity(p->getIcon(), p->getPosX(), p->getPosY());

    for (Entity *e : map.getEnemies())
    {
        m_renderer.drawEntity(e->getIcon(), e->getPosX(), e->getPosY());
    }
    for (Chest *c : map.getChests())
    {
        m_renderer.drawEntity('c', c->getPosX(), c->getPosY());
    }

    // Draw stats.
    m_renderer.clearPlayerRegion();
    m_renderer.drawPlayerStats(p->name, p->health, p->maxHealth, p->attackDamage, p->defense, p->mana, p->level, p->xp, p->xpToLevelUp);
}

void GameManager::playerActionMove()
{
    Map &map = Map::getInstance();
    Entity *p = map.getPlayer();

    m_playerRemainingMP = p->getMovementPoint();

    // Player move loop.
    int cursorX = p->getPosX(), cursorY = p->getPosY();
    int newX = cursorX, newY = cursorY;

    while (m_playerRemainingMP > 0)
    {
        redrawAll();

        const int MAX_MP_SIZE = 5 + 5 + 1;
        uint32_t distmap[MAX_MP_SIZE * MAX_MP_SIZE];
        bool rangemap[MAX_MP_SIZE * MAX_MP_SIZE];
        Map::getInstance().findDistanceToTilesRect(distmap, p->getPosX(), p->getPosY(), m_playerRemainingMP);
        Map::getInstance().getReachableTiles(rangemap, distmap, m_playerRemainingMP);

        const int bitmapSize = m_playerRemainingMP + m_playerRemainingMP + 1;
        m_renderer.drawBitmap(COLOR_RANGE, rangemap, p->getPosX() - m_playerRemainingMP, p->getPosY() - m_playerRemainingMP, bitmapSize, bitmapSize);
        m_renderer.drawColor(COLOR_CURSOR, cursorX, cursorY);

        // Draw actions.
        if (!m_nearbyEnemies.empty()) {
            m_renderer.drawAction("(A) Attack", 0);
        }
        if (!m_nearbyChests.empty()) {
            m_renderer.drawAction("(C) Open chest", 1);
        }

        WORD key = Input::getInstance().waitForInput();

        // Listen to action.
        switch (key)
        {
        case VK_UP:    if (newY != 0)                   newY--; break;
        case VK_DOWN:  if (newY != map.getHeight() - 1) newY++; break;
        case VK_LEFT:  if (newX != 0)                   newX--; break;
        case VK_RIGHT: if (newX != map.getWidth() - 1)  newX++; break;
        case VK_SPACE:
            movePlayerTo(cursorX, cursorY);
            updateNearbyEnemyAndChest();
            p->fillMana();
            break;
        case VK_RETURN:
            m_playerRemainingMP = 0;
            p->fillMana();
            break;
        case 'A':
            if (m_nearbyEnemies.empty() == false)
            {
                playerActionAttack();
            }
            break;
        case 'C':
            if (m_nearbyChests.empty() == false)
            {
               playerActionCollect();
            }
            break;
        }

        // Move cursor with check.
        if (isMoveValid(p, m_playerRemainingMP, newX, newY) && rangemap[(newY - p->getPosY() + m_playerRemainingMP) * bitmapSize + (newX - p->getPosX() + m_playerRemainingMP)]) {
            cursorX = newX;
            cursorY = newY;
        }
        else {
            newX = cursorX;
            newY = cursorY;
        }
    }

    redrawAll();
}

void GameManager::playerActionAttack()
{
    Map& map = Map::getInstance();
    Entity* p = map.getPlayer();
    int damage;

    if (m_nearbyEnemies.empty()) return;

    int enemyIndex = 0;
    bool done = false;
    while (!done)
    {
        Entity* selectedEnemy = m_nearbyEnemies[enemyIndex];

        m_renderer.drawRange(COLOR_ATTACK_RANGE, p->getPosX(), p->getPosY(), 1);
        m_renderer.drawColor(COLOR_CURSOR, selectedEnemy->getPosX(), selectedEnemy->getPosY());

        if (getDistance(p, selectedEnemy->getPosX(), selectedEnemy->getPosY()) == 1) {
            m_renderer.drawEnemyStats(selectedEnemy->name, selectedEnemy->health,
                selectedEnemy->getMaxHealth(), selectedEnemy->getAttackDamage(),
                selectedEnemy->getDefense());
        }

        // Draw actions.
        m_renderer.drawAction("(Left/Right) Select enemy", 0);
        m_renderer.drawAction("(Enter) Attack", 1);
        m_renderer.drawAction("(A) Cancel", 2);

        WORD key = Input::getInstance().waitForInput();

        // Listen to action.
        switch (key)
        {
        case VK_LEFT:
            enemyIndex--;
            if (enemyIndex == -1) enemyIndex = m_nearbyEnemies.size() - 1;
            break;
        case VK_RIGHT:
            enemyIndex++;
            if (enemyIndex == m_nearbyEnemies.size()) enemyIndex = 0;
            break;
        case 'S':
            m_renderer.clearPlayerRegion();
            m_renderer.drawMessage("You used a special attack on " + selectedEnemy->name + '!');
            waitForEnter();

            p->specialAttack(selectedEnemy);

            m_renderer.clearEnemyRegion();
            m_renderer.drawEnemyStats(selectedEnemy->name, selectedEnemy->health,
                selectedEnemy->getMaxHealth(), selectedEnemy->getAttackDamage(),
                selectedEnemy->getDefense());

            m_renderer.clearPlayerRegion();
            m_renderer.drawMessage("You dealt damage.");
            waitForEnter();

            if (selectedEnemy->isDead()) {
                m_renderer.clearPlayerRegion();
                m_renderer.drawMessage(selectedEnemy->name + " is dead!");
                waitForEnter();

                killEnemy(selectedEnemy);
            }

            updateNearbyEnemyAndChest();

            m_playerRemainingMP = 0;

            done = true;
            p->fillMana();
            break;

        case VK_RETURN:
            m_renderer.clearPlayerRegion();
            m_renderer.drawMessage("You attacked " + selectedEnemy->name + '!');
            waitForEnter();

            damage = p->attack(selectedEnemy);

            m_renderer.clearEnemyRegion();
            m_renderer.drawEnemyStats(selectedEnemy->name, selectedEnemy->health,
                selectedEnemy->getMaxHealth(), selectedEnemy->getAttackDamage(),
                selectedEnemy->getDefense());
            m_renderer.clearPlayerRegion();
            m_renderer.drawMessage("You dealt " + std::to_string(damage) + " damage.");
            waitForEnter();

            if (selectedEnemy->isDead()) {
                m_renderer.clearPlayerRegion();
                m_renderer.drawMessage(selectedEnemy->name + " is dead!");
                waitForEnter();

                killEnemy(selectedEnemy);
            }

            updateNearbyEnemyAndChest();

            // End turn automatically.
            m_playerRemainingMP = 0;

            done = true;
            p->fillMana();
            break;
        case 'A':
            done = true;
            break;
        }
    }

    m_renderer.clearEnemyRegion();
}

void GameManager::playerActionCollect()
{
    Map &map = Map::getInstance();
    Character *p = map.getPlayer();

    for (Chest *chest : m_nearbyChests) {
        Chest::Loot loot = p->openChest(chest);

        m_renderer.clearPlayerRegion();
        switch (loot) {
        case Chest::HEALTH:  m_renderer.drawMessage("You found a chest with " + std::to_string(chest->getHealth())       + " health!");        break;
        case Chest::ATTACK:  m_renderer.drawMessage("You found a chest with " + std::to_string(chest->getAttackDamage()) + " attack damage!"); break;
        case Chest::DEFENSE: m_renderer.drawMessage("You found a chest with " + std::to_string(chest->getDefense())      + " defense!");       break;
        case Chest::MANA:    m_renderer.drawMessage("You found a chest with " + std::to_string(chest->getMaxMana())         + " mana!");          break;
        }
        waitForEnter();
        p->fillMana();

        removeChest(chest);
    }

    updateNearbyEnemyAndChest();
}

void GameManager::enemyAction()
{
    for (Entity *enemy : Map::getInstance().getEnemies())
    {
        enemy->update();
    }

    if (Map::getInstance().getPlayer()->isDead()) {
        m_renderer.clearPlayerRegion();
        m_renderer.drawMessage("You are dead! Game over!");
        waitForEnter();
    }
}

bool GameManager::checkPlayerWin()
{
    if (hasPlayerWon()) {
        if (m_currentMap == 0) {
            m_renderer.clearPlayerRegion();
            m_renderer.drawMessage("Congratulations! You have completed the first dungeon!");
            waitForEnter();

            m_renderer.clearPlayerRegion();
            m_renderer.drawMessage("But your quest is not over yet. Onward, hero!");
            waitForEnter();

            m_currentMap++;
            loadNextMap();
        }
        else {
            m_renderer.clearPlayerRegion();
            m_renderer.drawMessage("You have completed the game!!!");
            waitForEnter();

            m_currentMap = 0;
            Map::getInstance().resetPlayerState();
            reloadMap();
        }

        return true;
    }

    return false;
}

void GameManager::checkPlayerDeath()
{
    if (Map::getInstance().getPlayer()->isDead()) {
        reloadMap();
    }
}

void GameManager::updateNearbyEnemyAndChest()
{
    Map& map = Map::getInstance();
    Character* p = map.getPlayer();

    m_nearbyEnemies.clear();
    m_nearbyChests.clear();

    for (Entity *enemy : map.getEnemies()) {
        if (getDistance(p, enemy->getPosX(), enemy->getPosY()) == 1) {
            m_nearbyEnemies.push_back(enemy);
        }
    }

    for (Chest *chest : map.getChests()) {
        if (getDistance(p, chest->getPosX(), chest->getPosY()) == 1) {
            m_nearbyChests.push_back(chest);
        }
    }
}

void GameManager::movePlayerTo(int x, int y)
{
    Map& map = Map::getInstance();
    Entity* p = map.getPlayer();

    m_playerRemainingMP -= getDistance(p, x, y);
    p->posX = x;
    p->posY = y;

    updateNearbyEnemyAndChest();
}

void GameManager::moveEnemyTo(Entity* entity, int x, int y)
{
    if (isEnemyMoveValid(entity, x, y))
    {
        Map::getInstance().removeWall(entity->posX, entity->posY);

        entity->posX = x;
        entity->posY = y;

        Map::getInstance().addWall(entity->posX, entity->posY);
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


bool GameManager::hasPlayerWon() const
{
    Map& map = Map::getInstance();
    return map.getEnemies().empty() && !map.getPlayer()->isDead();
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
