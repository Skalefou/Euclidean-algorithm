using System;

namespace piBenford
{
    class GestionFile
    {
        private StreamReader sr = new StreamReader("pi.txt");

        public bool end()
        {
            return sr.Peek() == -1;
        }
        public int read()
        {
            int a = sr.Read();
            return a - 48;
        }

        public bool isOver()
        {
            return true;
        }
    }
}