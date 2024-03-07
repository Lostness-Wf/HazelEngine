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
        private Rigidbody2DComponent m_Rigidbody;

        public Vector3 m_Velocity = Vector3.Zero;
        public float m_Speed = 10.0f;

        private Vector2 clickMousePosition = new Vector2(0);
        private Vector2 releaseMousePosition = new Vector2(0);
        private bool IsMouseLeftDown = false;

        void OnCreate()
        {
            m_Rigidbody = GetComponent<Rigidbody2DComponent>();
        }

        void OnUpdate(float ts)
        {
            if (Input.IsMouseDown(MouseCode.ButtonLeft) && !IsMouseLeftDown)
            {
                clickMousePosition = Input.GetMousePosition();
                IsMouseLeftDown = true;
            }

            if (!Input.IsMouseDown(MouseCode.ButtonLeft) && IsMouseLeftDown)
            {
                releaseMousePosition = Input.GetMousePosition();
                Vector2 delta = clickMousePosition - releaseMousePosition;
                Vector2 Delta = new Vector2(delta.X, -delta.Y);
                Console.WriteLine($"{Delta.X} {Delta.Y}");
                m_Rigidbody.ApplyLinearImpulse(Delta * 0.1f, true);
                IsMouseLeftDown = false;
            }
        }

    }
}