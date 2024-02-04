using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace CSharpSnakeGame
{
    [StructLayout(LayoutKind.Sequential)]
    public struct IntPair
    {
        public int First;
        public int Second;
        
        public IntPair(int first, int second)
        {
            First = first;
            Second = second;
        }
    }

    public enum MoveResult
    {
        Wall, Apple, Self, Void, Win
    }

    public class SnakyWrapper
    {
        private readonly IntPtr _snaky;

        [DllImport("libSnaky_wrapper.dll")]
        private static extern IntPtr Snaky_create(int initialX, int initialY, int size, int initialDirectionX, int initialDirectionY);

        [DllImport("libSnaky_wrapper.dll")]
        private static extern void Snaky_destroy(IntPtr handle);

        [DllImport("libSnaky_wrapper.dll")]
        private static extern int Snaky_turn(IntPtr handle, int newDirectionX, int newDirectionY);

        [DllImport("libSnaky_wrapper.dll")]
        private static extern int Snaky_nextStep(IntPtr handle);

        [DllImport("libSnaky_wrapper.dll")]
        private static extern void Snaky_getApplePosition(IntPtr handle, out int x, out int y);

        [DllImport("libSnaky_wrapper.dll")]
        private static extern void Snaky_getHeadPosition(IntPtr handle, out int x, out int y);

        [DllImport("libSnaky_wrapper.dll")]
        private static extern void Snaky_getSnakePositions(IntPtr handle, out IntPtr positionsArray, out int arrayLength);

        public SnakyWrapper(int initialX, int initialY, int size, IntPair initialDirection)
        {
            _snaky = Snaky_create(initialX, initialY, size, initialDirection.First, initialDirection.Second);
        }

        ~SnakyWrapper()
        {
            Snaky_destroy(_snaky);
        }

        public bool Turn(IntPair newDirection)
        {
            return Snaky_turn(_snaky, newDirection.First, newDirection.Second) != 0;
        }

        public MoveResult NextStep()
        {
            return (MoveResult)Snaky_nextStep(_snaky);
        }

        public IntPair GetApplePosition()
        {
            Snaky_getApplePosition(_snaky, out int x, out int y);
            return new IntPair { First = x, Second = y };
        }

        public IntPair GetHeadPosition()
        {
            Snaky_getHeadPosition(_snaky, out int x, out int y);
            return new IntPair { First = x, Second = y };
        }

        public List<IntPair> GetSnakePositions()
        {
            Snaky_getSnakePositions(_snaky, out var positionsArrayPtr, out var arrayLength);

            int[] positionsArray = new int[arrayLength]; // Assuming each position is represented by two integers (x, y)
            Marshal.Copy(positionsArrayPtr, positionsArray, 0, arrayLength);

            List<IntPair> positionsList = new List<IntPair>();
            for (int i = 0; i < arrayLength; i += 2)
            {
                positionsList.Add(new IntPair { First = positionsArray[i], Second = positionsArray[i + 1] });
            }

            return positionsList;
        }

        
    }
}
