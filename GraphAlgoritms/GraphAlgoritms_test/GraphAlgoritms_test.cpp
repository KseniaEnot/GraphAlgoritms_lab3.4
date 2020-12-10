#include "pch.h"
#include "CppUnitTest.h"
#include<fstream>
#include "../GraphAlgoritms/Graph.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define TEST_CASE_DIRECTORY GetDirectoryName(__FILE__)

namespace GraphAlgoritmstest
{
	TEST_CLASS(GraphAlgoritmstest)
	{
		string GetDirectoryName(string path) {
			const size_t last_slash_idx = path.rfind('\\');
			if (std::string::npos != last_slash_idx)
			{
				return path.substr(0, last_slash_idx + 1);
			}
			return "";
		}
	public:
		
		TEST_METHOD(InputTest)
		{
			string filename = std::string(TEST_CASE_DIRECTORY) + "in.txt";
			Graph g(2, filename);
			Assert::AreEqual(g.GetSize(), 2);
		}

		TEST_METHOD(WrongInputTest)
		{
			try { Graph g(2, "input.txt"); }
			catch (const exception& e) {
				Assert::AreEqual(e.what(), "Graph is empty");
			}
		}

		TEST_METHOD(Oooo) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "in.txt";
			Graph g(2, filename);
			Assert::AreEqual(g.GetSize(), 2);
			int realgraph[4] = { 0, 1, 1, 0 };
			Assert::IsTrue(g == realgraph);
		}

		TEST_METHOD(bft1) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testBFT1.txt";
			Graph g_bft(2, filename);
			Iterator* g_bft_iterator = g_bft.create_bft_iterator(0);
			Assert::AreEqual(g_bft_iterator->next(), 0);
			Assert::AreEqual(g_bft_iterator->next(), 1);
			Assert::AreEqual(g_bft_iterator->next(), 2);
			Assert::AreEqual(g_bft_iterator->next(), 5);
			Assert::AreEqual(g_bft_iterator->next(), 3);
			Assert::AreEqual(g_bft_iterator->next(), 6);
			Assert::AreEqual(g_bft_iterator->next(), 4);
			Assert::AreEqual(g_bft_iterator->next(), 7);
			Assert::AreEqual(g_bft_iterator->next(), 9);
			Assert::AreEqual(g_bft_iterator->next(), 8);
		}
		TEST_METHOD(bft2) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testBFT2.txt";
			Graph g_bft(2, filename);
			Iterator* g_bft_iterator = g_bft.create_bft_iterator(0);
			Assert::AreEqual(g_bft_iterator->next(), 0);
			Assert::AreEqual(g_bft_iterator->next(), 4);
			Assert::AreEqual(g_bft_iterator->next(), 5);
			Assert::AreEqual(g_bft_iterator->next(), 7);
			Assert::AreEqual(g_bft_iterator->next(), 8);
			Assert::AreEqual(g_bft_iterator->next(), 10);
			Assert::AreEqual(g_bft_iterator->next(), 2);
			Assert::AreEqual(g_bft_iterator->next(), 3);
			Assert::AreEqual(g_bft_iterator->next(), 6);
			Assert::AreEqual(g_bft_iterator->next(), 13);
			Assert::AreEqual(g_bft_iterator->next(), 14);
			Assert::AreEqual(g_bft_iterator->next(), 1);
			Assert::AreEqual(g_bft_iterator->next(), 9);
			Assert::AreEqual(g_bft_iterator->next(), 11);
			Assert::AreEqual(g_bft_iterator->next(), 15);
			Assert::AreEqual(g_bft_iterator->next(), 12);
		}

		TEST_METHOD(dft1) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testDFT1.txt";
			Graph g_dft(2, filename);
			Iterator* g_dft_iterator = g_dft.create_dft_iterator(0);
			Assert::AreEqual(g_dft_iterator->next(), 0);
			Assert::AreEqual(g_dft_iterator->next(), 5);
			Assert::AreEqual(g_dft_iterator->next(), 2);
			Assert::AreEqual(g_dft_iterator->next(), 1);
			Assert::AreEqual(g_dft_iterator->next(), 3);
			Assert::AreEqual(g_dft_iterator->next(), 4);
			Assert::AreEqual(g_dft_iterator->next(), 6);
			Assert::AreEqual(g_dft_iterator->next(), 7);
			Assert::AreEqual(g_dft_iterator->next(), 9);
			Assert::AreEqual(g_dft_iterator->next(), 8);
		}

		TEST_METHOD(dft2) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testDFT2.txt";
			Graph g_dft(2, filename);
			Iterator* g_dft_iterator = g_dft.create_dft_iterator(0);
			Assert::AreEqual(g_dft_iterator->next(), 0);
			Assert::AreEqual(g_dft_iterator->next(), 4);
			Assert::AreEqual(g_dft_iterator->next(), 8);
			Assert::AreEqual(g_dft_iterator->next(), 1);
			Assert::AreEqual(g_dft_iterator->next(), 2);
			Assert::AreEqual(g_dft_iterator->next(), 3);
			Assert::AreEqual(g_dft_iterator->next(), 6);
			Assert::AreEqual(g_dft_iterator->next(), 10);
			Assert::AreEqual(g_dft_iterator->next(), 9);
			Assert::AreEqual(g_dft_iterator->next(), 13);
			Assert::AreEqual(g_dft_iterator->next(), 14);
			Assert::AreEqual(g_dft_iterator->next(), 15);
			Assert::AreEqual(g_dft_iterator->next(), 11);
			Assert::AreEqual(g_dft_iterator->next(), 5);
			Assert::AreEqual(g_dft_iterator->next(), 7);
			Assert::AreEqual(g_dft_iterator->next(), 12);
		}

		TEST_METHOD(IfEulerian1)
		{
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfEulerian1.txt";
			Graph gIE(2, filename);
			Assert::IsTrue(gIE.IfEulerian());
		}

		TEST_METHOD(IfEulerian2)
		{
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfEulerian2.txt";
			Graph gIE(2, filename);
			Assert::IsTrue(gIE.IfEulerian());
		}

		TEST_METHOD(IfEulerian3)
		{
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfEulerian3.txt";
			Graph gIE(2, filename);
			Assert::IsFalse(gIE.IfEulerian());
		}

		TEST_METHOD(IfBipartite1) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfBipartite1.txt";
			Graph gIB(2, filename);
			Assert::IsTrue(gIB.IfBipartite());
		}

		TEST_METHOD(IfBipartite2) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfBipartite2.txt";
			Graph gIB(2, filename);
			Assert::IsTrue(gIB.IfBipartite());
		}

		TEST_METHOD(IfBipartite3) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfBipartite3.txt";
			Graph gIB(2, filename);
			Assert::IsFalse(gIB.IfBipartite());
		}

		TEST_METHOD(IfTree) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfTree1.txt";
			Graph gIT(2, filename);
			Assert::IsTrue(gIT.IfTree());
		}

		TEST_METHOD(IfTree2) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfTree2.txt";
			Graph gIT(2, filename);
			Assert::IsFalse(gIT.IfTree());
		}

		TEST_METHOD(IfTree3) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testIfTree3.txt";
			Graph gIT(2, filename);
			Assert::IsTrue(gIT.IfTree());
		}

		TEST_METHOD(PruferCode1) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testPruferCode1.txt";
			Graph gPC(2, filename);
			int* code = new int[gPC.GetSize() - 2];
			int realcode[] = { 1, 1, 5, 3, 6, 7, 6, 4 };
			code = gPC.PruferCode();
			for (int i = 0; i < gPC.GetSize() - 2; i++)
				Assert::AreEqual(code[i], realcode[i]);
		}

		TEST_METHOD(PruferCode2) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testPruferCode2.txt";
			Graph gPC(2, filename);
			int* code = new int[gPC.GetSize() - 2];
			int realcode[] = { 5, 2, 3, 2, 2, 2, 2, 9 };
			code = gPC.PruferCode();
			for (int i = 0; i < gPC.GetSize() - 2; i++)
				Assert::AreEqual(code[i], realcode[i]);
		}

		TEST_METHOD(PruferCode3) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testPruferCode3.txt";
			Graph gPC(2, filename);
			int* code = new int[gPC.GetSize() - 2];
			int realcode[] = { 1, 2, 9, 2, 6, 3, 7, 8 };
			code = gPC.PruferCode();
			for (int i = 0; i < gPC.GetSize() - 2; i++)
				Assert::AreEqual(code[i], realcode[i]);
		}

		TEST_METHOD(PruferDecode1) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testPruferDecode1.txt";
			Graph gP;
			fstream file; int length_Pruf;
			file.open(filename, ios::in);
			file >> length_Pruf;
			int* Pruf = new int[length_Pruf];
			for (int i = 0; i < length_Pruf; i++)
				file >> Pruf[i];
			file.close();
			gP.PruferDecode(Pruf, length_Pruf);
			Assert::AreEqual(gP.GetSize(), length_Pruf + 2);
			int realgraph[] = { 0, 1, 0, 0, 0, 1, 1, 0, 0, 0,
								1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
								0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
								0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
								0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
								1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
								0, 1, 1, 0, 0, 0, 0, 1, 0, 1,
								0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
			Assert::IsTrue(gP == realgraph);
		}

		TEST_METHOD(PruferDecode2) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testPruferDecode2.txt";
			Graph gP;
			fstream file; int length_Pruf;
			file.open(filename, ios::in);
			file >> length_Pruf;
			int* Pruf = new int[length_Pruf];
			for (int i = 0; i < length_Pruf; i++)
				file >> Pruf[i];
			file.close();
			gP.PruferDecode(Pruf, length_Pruf);
			Assert::AreEqual(gP.GetSize(), length_Pruf + 2);
			int realgraph[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
								0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
								0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
								0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
								1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
								0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
								0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
								0, 1, 0, 1, 1, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
			Assert::IsTrue(gP == realgraph);
		}

		TEST_METHOD(StrongConnection1) {
			string filename = std::string(TEST_CASE_DIRECTORY) + "tests//testStrongConnected1.txt";
			Graph gSC(2, filename);
			dualList* Sv = gSC.StrongConnected();
			int i = 0;
			while (!Sv[i].isEmpty())
			{
				for (size_t j = 0; j < Sv[i].get_size(); j++)
				{
					cout << Sv[i].at(j) << " ";
				}
				cout << endl;
				i++;
			}
		}
	};
}
