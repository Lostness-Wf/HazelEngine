﻿using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Hazel
{
    public class Input
    {
        public static bool IsKeyDown(KeyCode keycode)
        {
            return InternalCalls.Input_IsKeyDown(keycode);
        }
    }
}