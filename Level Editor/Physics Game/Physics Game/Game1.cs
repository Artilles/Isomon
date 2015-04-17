using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Physics_Game
{
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        public static Texture2D SimpleTexture;

        OOEntity target;
        OOEntity innerT;
        OOEntity sample;
        static Vector2 origin = new Vector2(400f, 400f);
        SpriteFont font;
        int x = 0;
        int y = 0;
        int time = 0;
        KeyboardState keyState;
        KeyboardState lastKeyState;
        Color _color = new Color();
        bool multiMove;
        Vector2 start;
        Vector2 end;
        bool drawing;
        int temp = 0;
        bool readKeys;
        bool rngColor;
        int encounterSet;

        MouseState mouseState = Mouse.GetState();
      

        List<OOEntity> tiles = new List<OOEntity>();

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        protected override void Initialize()
        {
           this.IsMouseVisible = true;
           base.Initialize();

           graphics.PreferredBackBufferHeight = 800;
           graphics.PreferredBackBufferWidth = 800;
           graphics.ApplyChanges();


           SimpleTexture = new Texture2D(GraphicsDevice, 1, 1, false,
           SurfaceFormat.Color);

           Int32[] pixel = { 0xFFFFFF }; // White. 0xFF is Red, 0xFF0000 is Blue
           SimpleTexture.SetData<Int32>(pixel, 0, SimpleTexture.Width * SimpleTexture.Height);

           target = new OOEntity(new Vector2(0,0), new Vector2(6, 6),1);
           innerT = new OOEntity(new Vector2(1, 1), new Vector2(3, 3), 1);
           sample = new OOEntity(new Vector2(620, 500), new Vector2(150, 150), 1);
           start = new Vector2(0, 0);
           end = new Vector2(0, 0);
           Color c1 = Color.White;
           innerT.color = Color.Magenta;
           innerT.color.A = 100;
           encounterSet = 1;
            drawing = false;
            readKeys = false;
           c1.A = 0;
           rngColor = false;
           _color = new Color(0, 0, 0);
           target.color = _color;
           target.color.A = 50;
           int count = 0;
           for (int y = 0; y < 100; y++)
           {
               for (int x = 0; x < 100; x++)
               {
                   tiles.Add(new OOEntity(new Vector2(x * 6, y * 6), new Vector2(5.9f, 5.9f),0));
                   tiles[count].color = c1;
                   tiles[count].altColor = c1;
                  // tiles[count].color.A = 0;
                   count++;
               }
           }

        }

        protected override void LoadContent()
        {
           spriteBatch = new SpriteBatch(GraphicsDevice);
           font = Content.Load<SpriteFont>("myFont");
        }

        protected override void Update(GameTime gameTime)
        {


            time+=2;
            if (time > 10) time = 0;

            // Allows the game to exit
            keyState = Keyboard.GetState();
            mouseState = Mouse.GetState();
            if (keyState.IsKeyDown(Keys.Escape))
                this.Exit();

            #region Encounter Zones
            if (keyState.IsKeyDown(Keys.LeftShift) && !lastKeyState.IsKeyDown(Keys.LeftShift))
            {
                if (!readKeys) readKeys = true;
                else readKeys = false;
            }
            #endregion
            #region Movement Controls
            if (keyState.IsKeyDown(Keys.Tab) && !lastKeyState.IsKeyDown(Keys.Tab))
            {
                if (multiMove) multiMove = false;
                else multiMove = true;
            }
            if (multiMove)
            {
                if (keyState.IsKeyDown(Keys.Left) && time == 10)
                { target.location.X -= 6f; x -= 1; }
                if (keyState.IsKeyDown(Keys.Right) && time == 10)
                { target.location.X += 6f; x += 1; }
                if (keyState.IsKeyDown(Keys.Up) && time == 10)
                { target.location.Y -= 6f; y -= 100; }
                if (keyState.IsKeyDown(Keys.Down) && time == 10)
                { target.location.Y += 6f; y += 100; }
            }
            else
            {
                if (keyState.IsKeyDown(Keys.Left) && !lastKeyState.IsKeyDown(Keys.Left))
                { target.location.X -= 6f; x -= 1; }
                if (keyState.IsKeyDown(Keys.Right) && !lastKeyState.IsKeyDown(Keys.Right))
                { target.location.X += 6f; x += 1; }
                if (keyState.IsKeyDown(Keys.Up) && !lastKeyState.IsKeyDown(Keys.Up))
                { target.location.Y -= 6f; y -= 100; }
                if (keyState.IsKeyDown(Keys.Down) && !lastKeyState.IsKeyDown(Keys.Down))
                { target.location.Y += 6f; y += 100; }
            }
            #endregion

            if (mouseState.LeftButton == ButtonState.Pressed || mouseState.RightButton == ButtonState.Pressed)
            {
                target.location.X = mouseState.X;
                target.location.Y = mouseState.Y;
                x = mouseState.X / 6;
                y = mouseState.Y / 6 * 100;
            }

            if (x > 100) x = 100;
            if (x < 0) x = 0;
            if (y > 9999) y = 10000;
            if (y < 0) y = 0;

            #region Colours
            if (keyState.IsKeyDown(Keys.D4) && !lastKeyState.IsKeyDown(Keys.D4))
            {
                if (!rngColor) rngColor = true;
                else rngColor = false;
            }
            if (!readKeys)
            {
                if ((keyState.IsKeyDown(Keys.Enter) || mouseState.LeftButton == ButtonState.Pressed) && !multiMove)
                { if (x + y < 10000) tiles[x + y].color = _color; }
                else if (keyState.IsKeyDown(Keys.Enter) || mouseState.LeftButton == ButtonState.Pressed && !drawing)
                {
                    start = new Vector2(x, y / 100);
                    drawing = true;
                }

                // if (drawing && (keyState.IsKeyUp(Keys.Enter) || mouseState.LeftButton == ButtonState.Released))
                if (drawing && (mouseState.LeftButton == ButtonState.Released))
                {
                    end.X = x;
                    end.Y = y;
                    end = new Vector2(x, y / 100);
                    drawing = false;
                    var r = new Random();
                    for (int xx = (int)start.X; xx < (int)end.X; xx++)
                    {
                        for (int yy = (int)start.Y; yy < (int)end.Y; yy++)
                        {
                            temp = xx + yy * 100;
                            if (temp < 10000)
                                tiles[xx + yy * 100].color = new Color(
                                    _color.R + r.Next(0, 20), 
                                    _color.G + r.Next(0, 20), 
                                    _color.B + r.Next(0, 20));
                        }
                    }
                }

                if (keyState.IsKeyDown(Keys.D1))
                { _color.R += 1; }
                if (keyState.IsKeyDown(Keys.D2))
                { _color.G += 1; }
                if (keyState.IsKeyDown(Keys.D3))
                { _color.B += 1; }
                if (keyState.IsKeyDown(Keys.Q))
                { _color.R -= 1; }
                if (keyState.IsKeyDown(Keys.W))
                { _color.G -= 1; }
                if (keyState.IsKeyDown(Keys.E))
                { _color.B -= 1; }
                if (keyState.IsKeyDown(Keys.RightShift) || mouseState.RightButton == ButtonState.Pressed)
                { if (x + y < 10000) _color = tiles[x + y].color; }
                sample.color = target.color = _color;
            }
            else
            {
                if (keyState.IsKeyDown(Keys.D1)
                    && !lastKeyState.IsKeyDown(Keys.D1))
                { encounterSet += 1; }
                if (keyState.IsKeyDown(Keys.D2)
                    && !lastKeyState.IsKeyDown(Keys.D2))
                { encounterSet -= 1; }

                if ((keyState.IsKeyDown(Keys.Enter) || mouseState.LeftButton == ButtonState.Pressed) && !multiMove)
                {
                    if (x + y < 10000) tiles[x + y].altColor = new Color(((encounterSet + 15) * 5) % 255, (encounterSet * 15) % 255, (encounterSet * 20) % 255);
                    if (x + y < 10000) tiles[x + y].encounterSet = encounterSet; 
                }
                else if (keyState.IsKeyDown(Keys.Enter) || mouseState.LeftButton == ButtonState.Pressed && !drawing)
                {
                    start = new Vector2(x, y / 100);
                    drawing = true;
                }

                // if (drawing && (keyState.IsKeyUp(Keys.Enter) || mouseState.LeftButton == ButtonState.Released))
                if (drawing && (mouseState.LeftButton == ButtonState.Released))
                {
                    end.X = x;
                    end.Y = y;
                    end = new Vector2(x, y / 100);
                    drawing = false;
                    for (int xx = (int)start.X; xx < (int)end.X; xx++)
                    {
                        for (int yy = (int)start.Y; yy < (int)end.Y; yy++)
                        {
                            temp = xx + yy * 100;
                            if (temp < 10000)
                            {
                                tiles[xx + yy * 100].altColor = new Color(((encounterSet + 15) * 5) % 255, (encounterSet * 15) % 255, (encounterSet * 20) % 255);
                                tiles[xx + yy * 100].encounterSet = encounterSet; 
                            }
                        }
                    }
                }
            }
            #endregion

            #region Models
            
            if (keyState.IsKeyDown(Keys.I))
            { 
                if (x + y < 10000) tiles[x + y].model = "tree";
            }
            if (keyState.IsKeyDown(Keys.O))
            {
                if (x + y < 10000) tiles[x + y].model = "girl";
            }
            #endregion

            #region File I/O
            if (keyState.IsKeyDown(Keys.F1))
            {
                // Compose a string that consists of three lines.
                string lines = "";

                for (int yy = 0; yy < 100; yy++)
                {
                    for (int xx = 0; xx < 100; xx++)
                    {
                        lines += tiles[xx + yy * 100].color.R.ToString() + " " + tiles[xx + yy * 100].color.G.ToString()
                            + " " + tiles[xx + yy * 100].color.B.ToString() + " "
                            + tiles[xx + yy * 100].encounterSet + " " + tiles[xx + yy * 100].model;
                        if (xx != 99)
                            lines += " ";
                    }
                    

                    lines += "\r\n";
                }

                // Write the string to a file.
                System.IO.StreamWriter file = new System.IO.StreamWriter("./test.txt");

                file.Write(lines);

                file.Close();

            }

            if (keyState.IsKeyDown(Keys.F2))
            {
                string[] lines = System.IO.File.ReadAllLines("./test.txt");
                int yy = 0;
                foreach (string line in lines)
                {                   
                    string[] tiles_ = line.Split(' ');
                    int count = 0;
                    int xx = 0;
                    foreach (string tile_ in tiles_)                      
                    {
                        int g = 0;
                        if (xx == 99)
                            g++;
                        try
                        {
                            if (count == 4)
                            {
                                tiles[xx + yy * 100].model = tile_;
                                xx++;
                                count++;
                            }
                            if (count == 3)
                            {
                                tiles[xx + yy * 100].encounterSet = Convert.ToInt32(tile_, 10);
                                count++;
                            }
                            if (count == 2)
                            {
                                tiles[xx + yy * 100].color.B = Convert.ToByte(tile_);
                                count++;
                            }
                            if (count == 1)
                            {
                                tiles[xx + yy * 100].color.G = Convert.ToByte(tile_);
                                count++;
                            }
                            if (count == 0)
                            {
                                tiles[xx + yy * 100].color.R = Convert.ToByte(tile_);
                                count++;
                            }
                            if (count == 5) count = 0;
                            if (xx == 100) xx--;
                        }
                        catch (FormatException e) {
                            /*Console.WriteLine("Input string is not a sequence of digits.");*/}    
                    }
                    yy++;
                    xx = 0;
                }
            }
            #endregion


            target.Update();
            innerT.location = new Vector2(target.location.X + 1, target.location.Y + 1);
           
            lastKeyState = keyState;
            
            base.Update(gameTime);
            
        }

        private void DrawText(GameTime gameTime)
        {
            spriteBatch.DrawString(font, _color.ToString(), new Vector2(600, 10), Color.White);
            spriteBatch.DrawString(font, time + "", new Vector2(600, 25), Color.White);
            spriteBatch.DrawString(font, "Multi: " + multiMove, new Vector2(600, 40), Color.White);
            spriteBatch.DrawString(font, "x: " + mouseState.X / 6, new Vector2(600, 55), Color.White);
            spriteBatch.DrawString(font, "y: " + mouseState.Y / 6, new Vector2(600, 70), Color.White);
            //spriteBatch.DrawString(font, "C: " + (x + y) , new Vector2(600, 85), Color.White);
            if (x + y < 10000)
            {
                spriteBatch.DrawString(font, ": " + tiles[x + y].color, new Vector2(600, 85), Color.White);
                spriteBatch.DrawString(font, "Enc. : " + tiles[x + y].encounterSet + "("+encounterSet+")", new Vector2(600, 100), Color.White);
                spriteBatch.DrawString(font, "Model: " + tiles[x + y].model, new Vector2(600, 130), Color.White);
      
            }
            spriteBatch.DrawString(font, "Enc. : " + readKeys, new Vector2(600, 115), Color.White);
            
            spriteBatch.DrawString(font, "start : " + start, new Vector2(600, 145), Color.White);

            spriteBatch.DrawString(font, "end : " + end, new Vector2(600, 160), Color.White);
        
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);
            spriteBatch.Begin(SpriteSortMode.Deferred,
                  BlendState.AlphaBlend);
            
            for (int g = 0; g < tiles.Count; g++)
            {
                if (!readKeys)
                    tiles[g].Draw(spriteBatch);
                else
                {  
                    tiles[g].DrawAlt(spriteBatch);
                    tiles[g].Draw(spriteBatch);
                }
            }
            
            target.Draw(spriteBatch);
            innerT.Draw(spriteBatch);
            sample.Draw(spriteBatch);
            DrawText(gameTime);
            spriteBatch.End();
            base.Draw(gameTime);
        }
    }
}
