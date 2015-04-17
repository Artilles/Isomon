using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Physics_Game
{
    class Entity
    {
        private Component[] components;

        public Entity() 
        { 
        }

        public void addComponent(Component c)
        {
            components[components.Length] = c;
        }

        public void removeComponent(Component c)
        {
        }
    }
}
