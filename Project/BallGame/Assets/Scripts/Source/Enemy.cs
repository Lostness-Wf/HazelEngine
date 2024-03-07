using System;

using Hazel;
using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Sandbox
{
    public class Enemy : Entity
    {
        private Rigidbody2DComponent m_Rigidbody;

        void OnCreate()
        {
            m_Rigidbody = GetComponent<Rigidbody2DComponent>();
        }

        void OnUpdate(float ts)
        {
            if (m_Rigidbody.LinearVelocity.LengthSquared() >= 10)
            {
                DestroyEntity(ID);
                Entity enemy = FindEntityByName("Enemy");
                if (enemy != null)
                {
                    Console.WriteLine("qwe");
                }
            }
        }
    }
}