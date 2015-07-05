#include "DataBase.h"
#include"AIE.h"
#include <sstream>
#include <iostream>

sqlite3 *ScoreDB::m_db;
const char * ScoreDB::file_db = "HighScore.db";

ScoreDB &ScoreDB::getInstance() // singleton
{
	static ScoreDB instance;
	return instance;
}

static int PrintScores(void* a_count, int numArgs, char **data, char **columnName)
{
	int &count = *(int*)a_count;
	
	for (int i = 0; i < numArgs; i += 2) // 2 values per score! Name and Score
	{
		DrawString(data[i], 215, 780 - 160 - 80 * count); // name
		DrawString(data[i + 1], 440, 780 - 160 - 80 * count); //  score
	}

	count++; 
	return 0;
}
void ScoreDB::Open() // open file
{
	sqlite3_open(file_db, &m_db);
	sqlite3_exec(m_db, "CREATE TABLE IF NOT EXISTS scores(name TEXT, score INT);", 0, 0, 0); // to make sure if file not exist this will create it
}
void ScoreDB::AddScore(int a_score, const char* a_name) // add score, name to the file 
{
	std::stringstream ss; 
	ss << "INSERT INTO scores(name, score) VALUES (" << "'" << a_name << "', " << a_score << ");"; // command to do that
	sqlite3_exec(m_db, ss.str().c_str(), 0, 0, 0);
}
void ScoreDB::DrawScores() // draw score on the screen and its also sort itself 
{
	int count = 0; // keep tract of the count of score
	sqlite3_exec(m_db, "SELECT * from scores order by SCORE asc;", PrintScores, &count, 0);
}
void ScoreDB::Close() // close the file
{
	sqlite3_close(m_db);
}

// Credit: Marco
struct Position { int x, y; }; // keep tract of the position where to print

static int PrintHighScore(void* a_pos, int numArgs, char **data, char **columnName)
{
		Position &p = *(Position*)a_pos;
		DrawString(data[0], p.x, p.y); // draw out the top score on the screen 
		return 0;	
}

void ScoreDB::HighScore(int x, int y) // function to get highscore
{
	//SELECT min(salary) FROM COMPANY;
	Position p = { x, y };
	sqlite3_exec(m_db, "SELECT min(score) FROM scores;", PrintHighScore, &p, 0); // command to select the  lowest score

	//char c_score[8]; // create a char so we can copy it in
	//itoa(m_scores[0].score, c_score, 10); // this is to copy the first score after sort onto the char we create
	//DrawString(c_score, x, y); // this is to draw it on the screen with position
}
