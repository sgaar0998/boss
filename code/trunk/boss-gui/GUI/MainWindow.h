/*	BOSS

	A "one-click" program for users that quickly optimises and avoids 
	detrimental conflicts in their TES IV: Oblivion, Nehrim - At Fate's Edge, 
	TES V: Skyrim, Fallout 3 and Fallout: New Vegas mod load orders.

    Copyright (C) 2009-2012    BOSS Development Team.

	This file is part of BOSS.

    BOSS is free software: you can redistribute 
	it and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation, either version 3 of 
	the License, or (at your option) any later version.

    BOSS is distributed in the hope that it will 
	be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BOSS.  If not, see 
	<http://www.gnu.org/licenses/>.

	$Revision: 2188 $, $Date: 2011-01-20 10:05:16 +0000 (Thu, 20 Jan 2011) $
*/

#ifndef __MAIN__HPP__
#define __MAIN__HPP__


#include "BOSS-Common.h"
#include "GUI/ElementIDs.h"
#include <wx/hyperlink.h>
#include <wx/progdlg.h>
#include <wx/thread.h>

//Program class.
class BossGUI : public wxApp {
public:
	virtual bool OnInit();
private:
	wxSingleInstanceChecker *checker;
	std::vector<uint32_t> detected;
};

wxDECLARE_EVENT(wxEVT_COMMAND_MYTHREAD_UPDATE, wxThreadEvent);

//Main frame class.
class MainFrame : public wxFrame, public wxThreadHelper {
public:
	MainFrame(const wxChar *title);
	void OnUpdateCheck(wxCommandEvent& event);
	void Update(std::string updateVersion);
	void OnOpenSettings(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnRunBOSS(wxCommandEvent& event);
	void OnOpenFile(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnRunTypeChange(wxCommandEvent& event);
	void OnFormatChange(wxCommandEvent& event);
	void OnGameChange(wxCommandEvent& event);
	void OnRevertChange(wxCommandEvent& event);
	void OnLogDisplayChange(wxCommandEvent& event);
	void OnUpdateChange(wxCommandEvent& event);
	void OnCRCDisplayChange(wxCommandEvent& event);
	void OnTrialRunChange(wxCommandEvent& event);
	void OnEditUserRules(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	inline void SetGames(std::vector<uint32_t> inGames);
	void DisableUndetectedGames();

	//Multithreaded update stuff.
	void CheckForUpdates();
	void OnThreadUpdate(wxThreadEvent& evt);
private:
	wxMenuBar *MenuBar;
	wxMenu *FileMenu;
	wxMenu *EditMenu;
	wxMenu *GameMenu;
	wxMenu *HelpMenu;
	wxButton *RunBOSSButton;
	wxButton *OpenBOSSlogButton;
	wxButton *EditUserRulesButton;
	wxCheckBox *ShowLogBox;
	wxCheckBox *CRCBox;
	wxCheckBox *UpdateBox;
	wxCheckBox *TrialRunBox;
	wxChoice *FormatChoice;
	wxChoice *RevertChoice;
	wxRadioButton *SortOption;
	wxRadioButton *UpdateOption;
	wxRadioButton *UndoOption;
	wxStaticText *RevertText;
	bool isStartup;
	std::vector<uint32_t> games;
protected:
	virtual wxThread::ExitCode Entry();
	uint32_t updateCheckCode;  //0 = update, 1 = no update, 2 = error.
	std::string updateCheckString;  //Holds wxMessageBox text.
	wxCriticalSection updateData; // protects fields above
	DECLARE_EVENT_TABLE()
};

class GUIMlistUpdater : public boss::MasterlistUpdater {
protected:
	int progress(boss::Updater * updater, double dlFraction, double dlTotal) {
		int currentProgress = (int)floor(dlFraction * 10);
		if (currentProgress == 1000)
			--currentProgress; //Stop the progress bar from closing in case of multiple downloads.
		wxProgressDialog* progress = (wxProgressDialog*)updater->progDialog;
		bool cont = progress->Update(currentProgress, "Downloading: " + updater->targetFile);
		if (!cont) {  //the user decided to cancel. Slightly temperamental, the progDia seems to hang a little sometimes and keypresses don't get registered. Can't do much about that.
			uint32_t ans = wxMessageBox(wxT("Are you sure you want to cancel?"), wxT("BOSS: Updater"), wxYES_NO | wxICON_EXCLAMATION, progress);
			if (ans == wxYES)
				return 1;
			progress->Resume();
		}
		return 0;
	}
};

class GUIBOSSUpdater : public boss::BOSSUpdater {
protected:
	int progress(boss::Updater * updater, double dlFraction, double dlTotal) {
		int currentProgress = (int)floor(dlFraction * 10);
		if (currentProgress == 1000)
			--currentProgress; //Stop the progress bar from closing in case of multiple downloads.
		wxProgressDialog* progress = (wxProgressDialog*)updater->progDialog;
		bool cont = progress->Update(currentProgress, "Downloading: " + updater->targetFile);
		if (!cont) {  //the user decided to cancel. Slightly temperamental, the progDia seems to hang a little sometimes and keypresses don't get registered. Can't do much about that.
			uint32_t ans = wxMessageBox(wxT("Are you sure you want to cancel?"), wxT("BOSS: Updater"), wxYES_NO | wxICON_EXCLAMATION, progress);
			if (ans == wxYES)
				return 1;
			progress->Resume();
		}
		return 0;
	}
};
#endif
