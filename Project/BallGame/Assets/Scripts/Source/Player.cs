using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Hazel;
using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Sandbox
{
    public class Player : Entity
    {
        private TransformComponent m_Transform;
        private Rigidbody2DComponent m_Rigidbody;
        private TextComponent m_TextComp;

        public float Speed;
        public float Time = 0.0f;

        bool clickLeft = false;

        Vector2 clickPosition = new Vector2(0);
        Vector2 releasePosition = new Vector2(0);
        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {ID}");

            m_Transform = GetComponent<TransformComponent>();
            m_Rigidbody = GetComponent<Rigidbody2DComponent>();
            m_TextComp = GetComponent<TextComponent>();
            m_TextComp.Text = "1236789";
            Console.WriteLine($"TEXT: {(string)m_TextComp.Text}");
        }

        void OnUpdate(float ts)
        {
            Time += ts;
            //Console.WriteLine($"Player.OnUpdate: {ts}");

            if (Input.IsMouseDown(MouseCode.ButtonLeft) && !clickLeft)
            {
                clickLeft = true;
                clickPosition = Input.GetMousePosition();
            }

            if (!Input.IsMouseDown(MouseCode.ButtonLeft) && clickLeft)
            {
                releasePosition = Input.GetMousePosition();
                Vector2 delta = clickPosition - releasePosition;
                delta = new Vector2(delta.X, -delta.Y);
                Console.WriteLine($"Delta: {delta.X} {delta.Y}");
                m_Rigidbody.ApplyLinearImpulse(delta * 0.2f, true);
                clickLeft = false;
            }

            float speed = Speed;
            Vector3 velocity = Vector3.Zero;

            if (Input.IsKeyDown(KeyCode.W))
                velocity.Y = 1.0f;
            else if (Input.IsKeyDown(KeyCode.S))
                velocity.Y = -1.0f;

            if (Input.IsKeyDown(KeyCode.A))
                velocity.X = -1.0f;
            else if (Input.IsKeyDown(KeyCode.D))
                velocity.X = 1.0f;

            Entity cameraEntity = FindEntityByName("Camera");
            if (cameraEntity != null)
            {
                Camera camera = cameraEntity.Cast<Camera>();

                if (Input.IsKeyDown(KeyCode.Q))
                    camera.DistanceFromPlayer += speed * 2.0f * ts;
                else if (Input.IsKeyDown(KeyCode.E))
                    camera.DistanceFromPlayer -= speed * 2.0f * ts;
            }

            velocity *= speed * ts;
            //Dynamic Entities
            m_Rigidbody.ApplyLinearImpulse(velocity.XY, true);

            //Static Entities
            //Vector3 translation = m_Transform.Translation;
            //translation += velocity * ts;
            //m_Transform.Translation = translation;
        }

    }
}