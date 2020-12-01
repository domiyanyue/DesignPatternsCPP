#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class SongInfo {
  private:
    std::string songName;
    std::string bandName;
    int yearReleased;

  public:
    SongInfo(std::string newSongName, std::string newBandName,
             int newYearReleased)
        : songName{newSongName}, bandName{newBandName}, yearReleased{
                                                            newYearReleased} {}

    std::string getSongName() { return songName; }

    std::string getBandName() { return bandName; }

    int getYearReleased() { return yearReleased; }

    void printInfo() {
        std::cout << "Song : " << songName << " Band Name: " << bandName
                  << " Year Released: " << yearReleased << "\n";
    }
};

class SongIterator {
  public:
    virtual bool hasNext() = 0;
    virtual SongInfo *next() = 0;
};

class SongOfThe70s : public SongIterator {
  private:
    std::vector<SongInfo *> bestSongs;
    int iteratorIndex = 0;

  public:
    SongOfThe70s() {
        addSong("Imagine", "John Lennon", 1971);
        addSong("American Pie", "Don Mclean", 1971);
        addSong("I Will Survive", "Gloria Gaynor", 1979);
    }

    void addSong(std::string songName, std::string bandName, int yearReleased) {
        SongInfo *song = new SongInfo(songName, bandName, yearReleased);
        bestSongs.push_back(song);
    }

    bool hasNext() { return iteratorIndex < bestSongs.size(); }

    SongInfo *next() {
        // assert ...
        return bestSongs[iteratorIndex++];
    }
};

class SongOfThe80s : public SongIterator {
  private:
    std::unordered_map<int, SongInfo *> bestSongs;
    int index = 0;
    int iteratorIndex = 0;

  public:
    SongOfThe80s() {
        addSong("Roam", "B52s", 1989);
        addSong("Cruel Summber", "Banananrama", 1984);
        addSong("head Over heals", "Tears for fears", 1985);
    }

    void addSong(std::string songName, std::string bandName, int yearReleased) {
        SongInfo *song = new SongInfo(songName, bandName, yearReleased);
        bestSongs[index++] = song;
    }

    bool hasNext() { return iteratorIndex < bestSongs.size(); }

    SongInfo *next() {
        // assert ...
        return bestSongs[iteratorIndex++];
    }
};

void printSongs(SongIterator *iter) {
    std::cout << "start print songs ...\n";
    while (iter->hasNext()) {
        iter->next()->printInfo();
    }
}

int main() {
    SongOfThe70s *s70 = new SongOfThe70s();
    SongOfThe80s *s80 = new SongOfThe80s();

    printSongs(s70);
    printSongs(s80);

    return 0;
}