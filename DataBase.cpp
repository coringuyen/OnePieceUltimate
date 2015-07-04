#include "DataBase.h"
#include"AIE.h"
#include <sstream>
#include <iostream>

sqlite3 *ScoreDB::m_db;
const char * ScoreDB::file_db = "HighScore.db";

ScoreDB &ScoreDB::getInstance()
{
	static ScoreDB instance;
	return instance;
}
static int PrintScores(void* a_count, int numArgs, char **data, char **columnName)
{
	int &count = *(int*)a_count;
	
	for (int i = 0; i < numArgs; i += 2) // 2 values per score! Name and Score
	{
		DrawString(data[i], 215, 780 - 160 - 80 * count);
		DrawString(data[i + 1], 440, 780 - 160 - 80 * count);
	}

	count++;
	return 0;
}
void ScoreDB::Open()
{
	sqlite3_open(file_db, &m_db);
	sqlite3_exec(m_db, "CREATE TABLE IF NOT EXISTS scores(name TEXT, score INT);", 0, 0, 0);
}
void ScoreDB::AddScore(int a_score, const char* a_name)
{
	std::stringstream ss;
	ss << "INSERT INTO scores(name, score) VALUES (" << "'" << a_name << "', " << a_score << ");";
	sqlite3_exec(m_db, ss.str().c_str(), 0, 0, 0);
}
void ScoreDB::DrawScores()
{
	int count = 0;
	sqlite3_exec(m_db, "SELECT * from scores order by SCORE desc;", PrintScores, &count, 0);
}
void ScoreDB::Close()
{
	sqlite3_close(m_db);
}