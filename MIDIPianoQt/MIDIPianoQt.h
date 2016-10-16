#ifndef MIDIPIANOQT_H
#define MIDIPIANOQT_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <qmessagebox.h>
#include "SettingsDialog.h"
#include "ui_MIDIPianoQt.h"
#include "myMIDI.h"
#include <set>


#ifndef REP
#define REP(i,n) for(i=0;i!=(n);++i)
#endif

#ifndef FOR
#define FOR(i,a,b) for(i=(a);i!=(b);++i)
#endif

#ifndef FORE
#define FORE(i,a,b) for(i=(a);i<=(b);++i)
#endif

class myButton:public QPushButton{
	Q_OBJECT
public:
	int index;
	myButton(QWidget *parent,int _index):index(_index),QPushButton(parent){}
};

class MIDIPianoQt : public QMainWindow{
	Q_OBJECT
public:
	MIDIPianoQt(QWidget *parent = 0);
	~MIDIPianoQt();
	void setupButtons(int minIndex,int maxIndex);
	void playNote(int note,int volume=100);
	void clearNote(int note);
	void stopNote(int note);
	void stopAll();
	bool isSubstained;
private slots:
	void doPressed(int index,int vol=-1);
	void doReleased(int index);
	void buttonPressed();
	void buttonReleased();
	void actionProcessor(QAction *);
private:
	Ui::MIDIPianoQtClass ui;
	SettingsDialog *configDlg;
	myButton *buttons[130];
	int _minIndex,_maxIndex;
	myMIDI *midiPointer;
	void showConfig();
	void keyPressEvent(QKeyEvent *);
	std::set<int> playedNotes;
};

class MIDICallback:public QObject{
	Q_OBJECT
public:
	std::function<void(long,long,long,long)> midiInCallback;
signals:
	void pressed(int note,int vol);
	void released(int note);
};

#endif // MIDIPIANOQT_H