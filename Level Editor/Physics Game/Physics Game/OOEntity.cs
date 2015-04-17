using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Physics_Game
{
    class OOEntity
    {
        public float mass;
        public Vector2 center = new Vector2(400f,400f);
        public Vector2 size;
        public Vector2 location;
        public OOEntity parent;
        public Color color;
        public Color altColor;
        public float angle;
        public float depth;
        public string model = "none";
        public int encounterSet = 0;

        public OOEntity() {}

        public OOEntity(Vector2 c, Vector2 s, float alpha)
        {
            this.location = c;
            this.size = s;
            this.depth = alpha;
        }
        public OOEntity(Vector2 c, Vector2 s, float m, float a)
        {
            this.mass = m;
            this.center.X += c.X;
            this.center.Y -= c.Y;
            this.size = s;
            location = center;
            location.X -= (s.X / 2);
            location.Y -= (s.Y / 2);
            angle = a;
        }

        public OOEntity(Vector2 c, Vector2 s, float m, OOEntity o)
        {
            this.mass = m;
            this.center.X += c.X;
            this.center.Y -= c.Y;
            this.size = s;
            location = center;
            location.X -= (s.X / 2);
            location.Y -= (s.Y / 2);
            parent = o;
            angle = 0f;
        }

        public OOEntity(Vector2 c, Vector2 s, float m, OOEntity o, float a)
        {
            this.mass = m;
            this.center.X += c.X;
            this.center.Y -= c.Y;
            this.size = s;
            location = center;
            location.X -= (s.X / 2);
            location.Y -= (s.Y / 2);
            parent = o;
            angle = a;
        }

        public void moveChild(Vector2 v)
        {
            if (parent != null)
            {
                location.X += v.X;
                if (location.X < parent.location.X
                    || location.X + size.X > parent.location.X + parent.size.X)
                    location.X -= v.X;
                location.Y -= v.Y;
                if (location.Y < parent.location.Y
                    || location.Y + size.Y > parent.location.Y + parent.size.Y)
                    location.Y += v.Y;
            }
        }

        public void move(Vector2 v)
        {
            location.X += v.X;
            location.Y -= v.Y;
        }

        public float moment()
        {
            float m = mass * (size.X * size.X + size.Y * size.Y) / 12;
            return m;
        }

        public float distance(Vector2 v)
        {
            double x = (double)Math.Pow(v.X - center.X, 2);
            double y = (double)Math.Pow(v.Y - center.Y, 2);
            float d = (float)Math.Sqrt(x + y);
            return d;
        }

        public void Update()
        {
            center = location;
            center.X += (size.X / 2) - 400f;
            center.Y += (size.Y / 2);

            center.Y = 400f - center.Y;
        }

        public void Draw(SpriteBatch s)
        {
            color.A = 50;
            Rectangle rect = new Rectangle((int)location.X, (int)location.Y, (int)size.X, (int)size.Y);
            Color temp = Color.Black;
            if (model != "none")
                s.Draw(Game1.SimpleTexture, rect, rect, temp, angle, new Vector2(0, size.Y / 2), 0, 0);
            else
                s.Draw(Game1.SimpleTexture, rect, rect, color, angle, new Vector2(0,size.Y/2),0,0);
            
        }
        public void DrawAlt(SpriteBatch s)
        {
            altColor.A = 40;
           // altColor = new Color(10, 10, 10);
            Rectangle rect = new Rectangle((int)location.X, (int)location.Y, (int)size.X, (int)size.Y);
            s.Draw(Game1.SimpleTexture, rect, rect, altColor, angle, new Vector2(0, size.Y / 2), 0, 0);
        }
    }
}
