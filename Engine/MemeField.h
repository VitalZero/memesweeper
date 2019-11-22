#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "Sound.h"

class MemeField
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
		void SpawnMeme();
		bool HasMeme() const;
		void Draw(const Vei2& screenPos, MemeField::State state, Graphics& gfx) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		bool HasNoNeighborMemes() const;
		void SetNeighborMemeCount(int nMemeCount);
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int nNeighborMemes = -1;
	};
public:
	MemeField(const Vei2& center, int nMemes );
	void Draw(Graphics& gfx) const;
	RectI GetRect() const;
	void OnRevealClick(const Vei2& screenPos);
	void OnFlagClick(const Vei2& screenPos);
	State GetState() const; 
private:
	void RevealTile(const Vei2& gridPos);
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Vei2 ScreenToGrid(const Vei2& screenPos);
	int CountNeighborMemes(const Vei2& gridPos);
	bool GameIsWon() const;
private:
	static constexpr int width = 10;
	static constexpr int height = 10;
	static constexpr int boderThickness = 5;	
	static constexpr Color borderColor = Colors::Blue;
	Sound sndLoose = Sound(L"spayed.wav");
	Vei2 topLeft;
	Tile field[width * height];
	State state = State::Memeing;
};