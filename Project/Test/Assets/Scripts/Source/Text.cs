using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Hazel;
using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Sandbox
{
    public class Text : Entity
    {
       public TextComponent textComp;
        void OnCreate()
        {
            textComp = GetComponent<TextComponent>();
        }

        void OnUpdate(float ts)
        {
        }

    }
}