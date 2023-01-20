#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>
#include "stemmer/estemmer.h"
#define fs fstream
#define mps map<string, int>

using namespace std;
mps stop,
    sports{{"ball", 0}, {"champion", 0}, {"competit", 0}, {"cup", 0}, {"feel", 0}, {"fifa", 0}, {"footbal", 0}, {"fun", 0}, {"game", 0}, {"habit", 0}, {"histroy", 0}, {"leagu", 0}, {"liga", 0}, {"play", 0}, {"player", 0}, {"popular", 0}, {"premier", 0}, {"race", 0}, {"score", 0}, {"soccer", 0}, {"sport", 0}, {"tactic", 0}, {"team", 0}, {"uefa", 0}, {"watch", 0}, {"world", 0}, {"year", 0}},
    sciences{{"academi", 0}, {"astronomi", 0}, {"biolog", 0}, {"chemistri", 0}, {"earth", 0}, {"econom", 0}, {"experiment", 0}, {"featur ", 0}, {" knowledg", 0}, {"mathemat", 0}, {"natur", 0}, {"physic", 0}, {"research", 0}, {"scienc", 0}, {"scientif", 0}, {"scientist", 0}, {"social", 0}, {"studi", 0}, {"test", 0}, {"theori", 0}, {"understand", 0}},
    politics{{"angri", 0}, {"author", 0}, {"backroom", 0}, {"ballot", 0}, {"broigus", 0}, {"cast", 0}, {"civic", 0}, {"citiz", 0}, {"comp", 0}, {"congress", 0}, {"countri", 0}, {"cryptocurr", 0}, {"defeat", 0}, {"democraci", 0}, {"deputri", 0}, {"diversity", 0}, {"elect", 0}, {"election", 0}, {"govern", 0}, {"head", 0}, {"irrit", 0}, {"jungl", 0}, {"leader", 0}, {"legislatur", 0}, {"minist", 0}, {"peopl", 0}, {"polit", 0}, {"presidenti", 0}, {"principl", 0}, {"reject", 0}, {"smith", 0}, {"support", 0}, {"vote", 0}, {"wilson", 0}},
    healths{{"act", 0}, {"aerob", 0}, {"afford", 0}, {"athlet", 0}, {"bodybuild", 0}, {"care", 0}, {"cheap", 0}, {"cigna", 0}, {"club", 0}, {"compani", 0}, {"compar", 0}, {"crunch", 0}, {"diet", 0}, {"doctor", 0}, {"ehealthinsur", 0}, {"exercis", 0}, {"fit", 0}, {"fitnessstudio", 0}, {"gym", 0}, {"health", 0}, {"healthcar", 0}, {"home", 0}, {"hour", 0}, {"insur", 0}, {"la", 0}, {"lifetim", 0}, {"lose", 0}, {"loss", 0}, {"manag", 0}, {"medic", 0}, {"nutrit", 0}, {"obama", 0}, {"onlin", 0}, {"person", 0}, {"pilat", 0}, {"planet", 0}, {"privat", 0}, {"tip", 0}, {"trainer", 0}, {"unit", 0}, {"weight", 0}, {"workout", 0}, {"world", 0}},
    arts{{"acrobat", 0}, {"adorn", 0}, {"aesthet", 0}, {"architectur", 0}, {"art", 0}, {"auditori", 0}, {"balanc", 0}, {"ballet", 0}, {"calligraphicameo", 0}, {"ceram", 0}, {"cinema", 0}, {"circus", 0}, {"clown", 0}, {"color", 0}, {"compositconceptu", 0}, {"ook", 0}, {"creativ", 0}, {"ube", 0}, {"cultur", 0}, {"cylind", 0}, {"danc", 0}, {"decor", 0}, {"depth", 0}, {"design", 0}, {"dimension", 0}, {"drama", 0}, {"draw", 0}, {"ye", 0}, {"embroid", 0}, {"mphasi", 0}, {"feel", 0}, {"film", 0}, {"form", 0}, {"galleri", 0}, {"ame", 0}, {"height", 0}, {"histori", 0}, {"hue", 0}, {"idea", 0}, {"magin", 0}, {"innov", 0}, {"inspir", 0}, {"intens", 0}, {"inton", 0}, {"jewelri", 0}, {"inesthetlegend", 0}, {"line", 0}, {"literatur", 0}, {"look", 0}, {"magic", 0}, {"ime", 0}, {"movementmuseum", 0}, {"music", 0}, {"object", 0}, {"oil", 0}, {"ornamentpaint", 0}, {"palac", 0}, {"paleolith", 0}, {"passion", 0}, {"erform", 0}, {"hotographiplastic", 0}, {"oetri", 0}, {"proport", 0}, {"rose", 0}, {"puppet", 0}, {"pyramid", 0}, {"ualiti", 0}, {"realism", 0}, {"epresent", 0}, {"rhythm", 0}, {"rich", 0}, {"ock", 0}, {"sculpturshape", 0}, {"sing", 0}, {"skill", 0}, {"sphere", 0}, {"sport", 0}, {"stage", 0}, {"talent", 0}, {"technic", 0}, {"textur", 0}, {"theater", 0}, {"heatr", 0}, {"theauthortone", 0}, {"uniti", 0}, {"valu", 0}, {"varieti", 0}, {"isual", 0}, {"wax", 0}},
    economics{{"account", 0}, {"advantag", 0}, {"agreement", 0}, {"assest", 0}, {"balanc", 0}, {"bear", 0}, {"bull", 0}, {"busi", 0}, {"compar", 0}, {"cost", 0}, {"countri", 0}, {"cycl", 0}, {"deflat", 0}, {"demand", 0}, {"divis", 0}, {"domest", 0}, {"economi", 0}, {"elast", 0}, {"export", 0}, {"financi", 0}, {"fiscal", 0}, {"gross", 0}, {"growth", 0}, {"hand", 0}, {"incom", 0}, {"inflat", 0}, {"invis", 0}, {"joint", 0}, {"knight", 0}, {"labour", 0}, {"law", 0}, {"liquid", 0}, {"margin", 0}, {"market", 0}, {"oligopoli", 0}, {"opportun", 0}, {"polici", 0}, {"product", 0}, {"rate", 0}, {"sheet", 0}, {"stagflat", 0}, {"strategi", 0}, {"suppli", 0}, {"tax", 0}, {"white", 0}};

void tokens(fs &file, mps &mp, mps &stop)
{
    float size = 0;
    while (!file.eof())
    {
        size++;
        string str;
        file >> str;
        stemmer(str);
        if (!(stop.find(str) != stop.end()))
            mp[str]++;
    }
}

void similarity(mps &mp)
{
    int sport = 0, art = 0, science = 0, politic = 0, health = 0, economic = 0;
    for (auto &it : mp)
    {
        sport += (sports.find(it.first) != sports.end());
        art += (arts.find(it.first) != arts.end());
        science += (sciences.find(it.first) != sciences.end());
        politic += (politics.find(it.first) != politics.end());
        health += (healths.find(it.first) != healths.end());
        economic += (economics.find(it.first) != economics.end());
    }
    if (sport > art && sport > science && sport > politic && sport > health && sport > economic)
        cout << " sport\n";
    else if (art > sport && art > science && art > politic && art > health && art > economic)
        cout << " art\n";
    else if (science > sport && science > art && science > politic && science > health && science > economic)
        cout << " science\n";
    else if (health > sport && health > art && health > politic && health > science && health > economic)
        cout << " health\n";
    else if (politic > sport && politic > art && politic > science && politic > health && politic > economic)
        cout << " politics\n";
    else if (economic > sport && economic > art && economic > science && economic > health && economic > politic)
        cout << " economics\n";
    else
        cout << " unknown\n";
}

void print(mps &mp)
{
    for (auto &it : mp)
    {
        cout << "." << it.first << setw(40 - (it.first).size()) << "\t"; // << it.second << endl;
    }
}
int main()
{
    // declaration
    fs stopWords("stopwords.txt");
    string str;
    mps test;
    //  put the stop words in map
    while (!stopWords.eof())
    {
        string str;
        stopWords >> str;
        stemmer(str);
        stop[str];
    }
    stopWords.close();
    for (int i = 1; i <= 30; i++)
    {
        mps test;
        cout << "Article " << i << " is talking about ";
        ostringstream filename;
        filename << i << ".txt";
        fs file(filename.str());
        tokens(file, test, stop);
        similarity(test);
        file.close();
    }
    cout << "Enter the name of file you want to test it's classification : ";
    cin >> str;
    fs test_file(str);
    tokens(test_file, test, stop);
    similarity(test);

    return 0;
}