#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "Sound.h"

class MemeField
{
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
		void Draw(const Vei2& screenPos, bool fucked, Graphics& gfx) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
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
	bool GameIsWon() const;
	bool GameIsLost() const;
private:
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Vei2 ScreenToGrid(const Vei2& screenPos);
	int CountNeighborMemes(const Vei2& gridPos);
private:
	static constexpr int width = 5;
	static constexpr int height = 5;
	static constexpr int boderThickness = 5;	
	static constexpr Color borderColor = Colors::Blue;
	Sound sndLoose = Sound(L"spayed.wav");
	Vei2 topLeft;
	Tile field[width * height];
	bool isFucked = false;
};