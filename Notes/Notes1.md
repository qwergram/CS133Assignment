# Sorting Classes

In the last couple of weeks, a couple of concepts have been taught to us regarding sorting,
inheritance, virtual inheritance and with it a bunch of headaches. This guide here is my way
of documenting these headaches so I don't run into them again. Hopefully you'll find them
just as useful.

## Context

Imagine the following scenario: we have a couple of game entities that we'd like to sort. Perhaps
our intention is to find the strongest entity on the board, perhaps that might be a boss, player,
or even a random mob. Let's quickly sketch out our `Entity` class and then build on it.

Let's define what it means to be stronger. In our purpose, we want to know who would still be
standing if two entities went at each other. This means the entity with the highest damage output
plus their health is the "stronger" one.

For instance, if an entity wields a sword that deals five damage, and has ten health, they have a total
strength of 15. If paired against another entity that wields a tome (8 damage) and has nine health,
they would be the weaker one because the latter entity has a strength of 17.

<table>
<tr>
<td>Entity 1</td>
<td>Damage: 5</td>
<td>Health: 10</td>
<td>Strength: 15</td>
<td>(Weaker)</td>
</tr>
<tr>
<td>Entity 2</td>
<td>Damage: 8</td>
<td>Health: 9</td>
<td>Strength: 17</td>
<td>(Stronger)</td>
</tr>
</table>

## Pure Virtual `Entity`

```cpp
class Entity {
public:
    Entity(int health) {};
    ~Entity() {};
    
    // For calculating strength
    virtual int strength()const = 0;

    // Comparison
    virtual bool operator>(const Entity & lhs)const = 0;
    virtual bool operator<(const Entity & lhs)const = 0;
    virtual bool operator>=(const Entity & lhs)const = 0;
    virtual bool operator<=(const Entity & lhs)const = 0;
    virtual bool operator==(const Entity & lhs)const = 0;
    virtual bool operator!=(const Entity & lhs)const = 0;
    
    // Be able to tell what this is
    virtual void print()const = 0;
    
    // Game stuff
    virtual void battleCry()const = 0;
    virtual void heal() = 0;
    virtual void damage() = 0;
    virtual void attack(Entity & enemy)const = 0;
}
```

So here, we defined a pure virtual class, which is something we can use as a parent class
for anything else we want. So let's create a couple more classes.

## `Human` Class

Naturally, I would want to take part in this game, so let's define these values for a human.
For the sake of brevity, I've included the definitions and declarations all in once place.

```cpp
class Human : virtual public Entity {
public:
    Human(int health, int swordDamage) : Entity(health) {
        this->m_health = health;
        this->m_sword = swordDamage;
    };
    ~Human() {};

    virtual int strength()const {
        return this->m_health + this->m_sword;
    };

    virtual bool operator>(const Entity & lhs)const {
            
    };

    virtual bool operator<(const Entity & lhs)const = 0;
    virtual bool operator>=(const Entity & lhs)const = 0;
    virtual bool operator<=(const Entity & lhs)const = 0;
    virtual bool operator==(const Entity & lhs)const = 0;
    virtual bool operator!=(const Entity & lhs)const = 0;
    
    // Be able to tell what this is
    virtual void print()const = 0;
    
    // Game stuff
    virtual void battleCry()const = 0;
    virtual void heal() = 0;
    virtual void damage() = 0;
    virtual void attack(Entity & enemy)const = 0;
private:
    int m_health;
    int m_sword;
}

```
