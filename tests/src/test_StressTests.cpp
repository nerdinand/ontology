#include <gmock/gmock.h>
#include <ontology/Ontology.hpp>

#define NAME Stress

using namespace Ontology;

// ----------------------------------------------------------------------------
// test fixture
// ----------------------------------------------------------------------------

struct Position : public Component
{
    Position(int x, int y) : x(x), y(y) {}
    int x, y;
};
inline bool operator==(const Position& lhs, const Position rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct Movement : public System
{
    void initialise() override {}
    void processEntity(Entity& e) override
    {
        e.getComponent<Position>().x += 2;
        e.getComponent<Position>().y += 1;
    }
};

// ----------------------------------------------------------------------------
// tests
// ----------------------------------------------------------------------------

TEST(NAME, ThousandEntities)
{
    World world;
    world.getSystemManager()
        .addSystem(new Movement)
        .initialise()
        ;
    for(int i = 0; i != 1000; ++i)
        world.getEntityManager().createEntity("entity")
            .addComponent(new Position(0, 0))
            ;
    for(int i = 0; i != 1000; ++i)
        world.update();

    for(auto& entity : world.getEntityManager().getEntityList())
    {
        ASSERT_EQ(Position(2000, 1000), entity->getComponent<Position>());
    }
}