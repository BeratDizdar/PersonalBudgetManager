#include <iostream>
#include <vector>
#include <string>
/******************************************************************************
* MAKROLAR
******************************************************************************/
#define CLEAR           "\033[2J\033[1;1H"

#define COLOR(color)    "\033[" << color << "m"
#define RESET           "0"
#define FG_BLACK        "30"
#define BG_BLACK        "40"
#define FG_RED          "31"
#define BG_RED          "41"
#define FG_GREEN        "32"
#define BG_GREEN        "42"
#define FG_YELLOW       "33"
#define BG_YELLOW       "43"
#define FG_BLUE         "34"
#define BG_BLUE         "44"
#define FG_MAGENTA      "35"
#define BG_MAGENTA      "45"
#define FG_CYAN         "36"
#define BG_CYAN         "46"
#define FG_WHITE        "37"
#define BG_WHITE        "47"
/******************************************************************************
* ENTRY CLASS
******************************************************************************/
class BudgetEntry {
private:
    std::string _description;
    double _amount;
public:
    BudgetEntry(const std::string& desc, double amt) {
        _description = desc;
        _amount = amt;
    }

    std::string getDescription() const {
        return _description;
    }
    void setDescription(const std::string& desc) {
        _description = desc;
    }
    double getAmount() const {
        return _amount;
    }
    void setAmount(double amt) {
        _amount = amt;
    }
};
/******************************************************************************
* MANAGER CLASS
******************************************************************************/
class BudgetManager {
    std::vector<BudgetEntry> entries;
public:
    
    /* EKLEME İŞLEVİ ********************************************************
    ************************************************************************/
    std::string enterDesc() {
        std::cout << "Enter the description for the entry\n>> ";
        std::string desc; std::cin >> desc;
        return desc;
    }
    double enterAmt() {
        std::cout << "Enter the amount of the entry\n>> ";
        double amt; std::cin >> amt;
        return amt;
    }
    void addEntry(const std::string& desc, double amt) {
        entries.push_back(BudgetEntry(desc, amt));
    }

    /* SİLME İŞLEVİ *********************************************************
    ************************************************************************/
    size_t enterIndex() {
        std::cout << "Enter the index of the entry you want to delete\n";
        int i = 1;
        for (auto& entry : entries) {
            std::cout << i << ". " << entry.getDescription() << std::endl;
            i++;
        } std::cout << ">> ";
        size_t index = 0; std::cin >> index;
        return index;
    }
    void removeEntry(size_t index) { 
        if(index-1 < entries.size()) {
            entries.erase(entries.begin() + index-1);
            std::cout << "Entry deleted successfully.\n>> ";
        }
        else {
            std::cerr << "Invalid index!\n>> ";
        }
    }

    /* GÖRÜNTÜLEME İŞLEVİ ***************************************************
    ************************************************************************/
    void displayEntries() {
        std::cout << COLOR(FG_YELLOW) << "\n** Bugdet Entries **\n" << "********************" << COLOR(RESET) << std::endl;
        for (const auto& entry : entries) {
            if (entry.getAmount() < 0) {
                std::cout << entry.getDescription() << "\nL--->(" << COLOR(FG_RED) << entry.getAmount() << COLOR(RESET) << "TL)\n\n";
            } else {
                std::cout << entry.getDescription() << "\nL--->(" << COLOR(FG_GREEN) << entry.getAmount() << COLOR(RESET) << "TL)\n\n";
            }
        }
        std::cout << ">> ";
    }

    /* TOPLAMA İŞLEVİ *******************************************************
    ************************************************************************/
    void displayTotal() {
        double total = 0;
        std::cout << COLOR(FG_YELLOW) << "\n** Total Budget **\n" << "******************" << COLOR(RESET) << std::endl;
        for (const auto& entry : entries) {
            total += entry.getAmount();
        }
        if (total < 0) {
            std::cout << COLOR(FG_RED) << total << "TL\n";
        } else {
            std::cout << COLOR(FG_GREEN) << total << "TL\n";
        }
        std::cout << COLOR(RESET) << ">> ";
    }

    /* KOMUTLARI GÖSTERME İŞLEVİ ********************************************
    ************************************************************************/
    void displayInstruction() {
        std::cout << COLOR(FG_MAGENTA) << "** Personal Budget Manager **\n" << "*****************************\n" << COLOR(RESET);
        std::cout << "1.Add Entry\n2.Remove Entry\n3.Display Entries\n4.Display Total Budget\n5.Help\n6.Quit\n>> ";
    }
};
/******************************************************************************
* ANA FONKSİYON
******************************************************************************/
int main(){

    BudgetManager bm;
    std::string desc;
    double amount;
    short choice;
    int index;

    bm.displayInstruction();
    while (1) {
        std::cin >> choice;
        switch (choice) {
            case 1:
                desc = bm.enterDesc();
                amount = bm.enterAmt();
                bm.addEntry(desc,amount); break;
            case 2:
                index = bm.enterIndex();
                bm.removeEntry(index);    break;
            case 3:
                bm.displayEntries();      break;
            case 4:
                bm.displayTotal();        break;
            case 5:
                bm.displayInstruction();  break;
            case 6:
                exit(1); break;
            default: std::cout << COLOR(FG_RED) << "Invalid choice!\n" << COLOR(RESET) << ">> "; break;
        }
    }
    
    return 0;
}