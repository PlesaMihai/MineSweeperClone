#pragma once
#include "Graphics.h"
#include "Sound.h"

class MineField
{
public:
	enum class State
	{
		Fucked,
		Winrar,
		Memeing
	};
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMine();
		bool HasMine() const;
		void Draw(const Vei2& screenPos,MineField::State fieldState, Graphics& gfx) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		bool HasNoNeighborMemes() const;
		void SetNeighborMemeCount(int memeCount);
	private:
		State state = State::Hidden;
		bool hasMine = false;
		int nNeighborMemes = -1;
	};

public:
	MineField(const Vei2& center, int nMines);
	void Draw(Graphics& gfx) const;
	RectI GetRect() const;
	void OnRevealClick(const Vei2& screenPos);
	void OnFlagClick(const Vei2& screenPos);
	State GetState() const;
private:
	void Revealtile(const Vei2& gridPos);
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Vei2 ScreenToGrid(const Vei2& screenPos);
	int CountNeighborMemes(const Vei2& gridPos);
	bool GameIsWon() const;
private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	static constexpr int borderThickness = 10;
	static constexpr Color borderColor = Colors::Blue;
	Sound sndLose = Sound(L"spayed.wav");
	State state = State::Memeing;
	Tile field[width * height];
	Vei2 topLeft;
};