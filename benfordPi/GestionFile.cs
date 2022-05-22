using System;

namespace piBenford
{
    class GestionFile
    {
        private StreamReader sr = new StreamReader("pi.txt");
        public int read()
        {
           int a = sr.Read();
           return a;
        }

        public bool isOver()
        {
            return true;
        }
    }
}