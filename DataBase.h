#pragma once
#include "sqlite3.h"

class ScoreDB
{
	static sqlite3 *m_db;
	static const char *file_db;
<<<<<<< HEAD

=======
>>>>>>> origin/master
	ScoreDB() {}

public:
	static ScoreDB &getInstance();
	static void Open();
	static void AddScore(int a_score, const char* a_name);
	static void DrawScores();
	static void Close();
<<<<<<< HEAD
	static void HighScore(int x, int y);
=======
>>>>>>> origin/master
};