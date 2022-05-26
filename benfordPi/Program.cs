using piBenford;
using System;

namespace piBenford
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("PiBenford by Skalefou\nOccurrence of digits in the number Pi");
			GestionFile file = new GestionFile();
			int[] number = new int[10];
			Array.Fill(number, 0);
			while (!file.end())
			{
				int f = file.read();
				if(f >= 0)
					number[f]++;
			}
			for(int i = 0; i < 10; i++)
			{
				Console.WriteLine(i + " : " + number[i]);
			}
			Console.Read();
		}
	}

}