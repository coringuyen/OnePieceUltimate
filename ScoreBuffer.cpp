#include "ScoreBuffer.h"
#include <fstream>
#include "Aie.h"
#include <cstring>
#include <iostream>


int ScoreBuffer::m_nScores = 0;				// Number of scores
ScoreData *ScoreBuffer::m_scores = nullptr; // Array of scores
const char *ScoreBuffer::m_path = "scores.dat";

void ScoreBuffer::load() // this is to open file and load the scores in
{
	std::fstream fin;
	fin.open(m_path, std::ios_base::binary | std::ios_base::in);
	if (fin.is_open())
	{
		fin >> m_nScores;
		m_scores = new ScoreData[m_nScores];
		fin.read((char*)m_scores, sizeof(ScoreData)*m_nScores);
	}
	fin.close();
}
void ScoreBuffer::draw(int x, int y) // this is to draw the score on the screen
{                                
	int Scorenum;
	for (int i = 0; i < m_nScores && i < 10; ++i)
	{
		Scorenum = i + 1;
		char c_score[8];
		char cnum[8];
		char output[16];
		
		itoa(m_scores[i].score, c_score, 10);
		itoa(Scorenum, cnum, 10);
		cnum[1] = ':';
		cnum[2] = 0;

		strcpy_s(output, 16, m_scores[i].m_name);
		strcat_s(output, cnum);
		//DrawString(m_scores[i].m_name, x, y - i * 40);
		DrawString(c_score, x + 200, y - i * 40);
		DrawString(output, x, y - i * 40);
	}
}
void ScoreBuffer::save() // save score after finish the game
{
	std::fstream fout;
	fout.open(m_path, std::ios_base::binary | std::ios_base::out);
	if (fout.is_open())
	{
		fout << m_nScores;
		fout.write((char*)m_scores, sizeof(ScoreData)*m_nScores);
		delete[] m_scores;
		m_scores = nullptr;
	}
	fout.close();
}

void SD_swap(ScoreData &a, ScoreData &b) { ScoreData t = a; a = b; b = t; } // swap the 2 score
bool SD_cmp(ScoreData a, ScoreData b) { return a.score < b.score; } // compare 2 score
void ScoreBuffer::sort()
{
	for (int j = 0; j < m_nScores; ++j)
		for (int i = 0; i < m_nScores - 1; ++i)
		{
		if (SD_cmp(m_scores[i + 1], m_scores[i]))
			SD_swap(m_scores[i + 1], m_scores[i]);
		}
}
void ScoreBuffer::HighScore(int x, int y) // Credit: Eric. this is to draw the best score.
{
	if (m_nScores == 0) return; // idk this line i forgot

	char c_score[8]; // create a char so we can copy it in
		itoa(m_scores[0].score, c_score, 10); // this is to copy the first score after sort onto the char we create
		DrawString(c_score, x, y); // this is to draw it on the screen with position
}

void ScoreBuffer::addScore(ScoreData a_score) // this is to add new score to the old score. I need an explain on how to use this 
{
	ScoreData *old_scores  = m_scores;
	m_scores = new ScoreData[m_nScores + 1];

	for (int i = 0; i < m_nScores; ++i)
		m_scores[i] = old_scores[i];

	delete[] old_scores;

	m_scores[m_nScores] = a_score;
	m_nScores++;
}