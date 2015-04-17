using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Physics_Game
{
    interface Component
    {
        void componentAdded(Component c);
        void componentRemoved(Component c);
    }
}
