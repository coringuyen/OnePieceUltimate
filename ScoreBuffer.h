#pragma once
struct ScoreData // doesn't matter what's in here
{
	float score;
	char m_name[16];	
};

class ScoreBuffer // Mainly static class for global access
{
	static int m_nScores;		// Number of scores
	static ScoreData *m_scores; // Array of scores
	static const char *m_path;
	ScoreBuffer() {}
public:
	static void load();
	static void draw(int x, int y);
	static void save();
	static void sort();
	static void addScore(ScoreData a_score);
	static void HighScore(int x, int y);
};