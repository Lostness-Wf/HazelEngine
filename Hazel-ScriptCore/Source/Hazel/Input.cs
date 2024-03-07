using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Hazel
{
    public class Input
    {
        public static bool IsKeyDown(KeyCode keycode)
        {
            return InternalCalls.Input_IsKeyDown(keycode);
        }

        public static bool IsMouseDown(MouseCode mousecode)
        {
            return InternalCalls.Input_IsMouseDown(mousecode);
        }

        public static Vector2 GetMousePosition()
        {
            InternalCalls.Input_GetMousePosition(out Vector2 mouseposition);
            return mouseposition;
        }
    }
}