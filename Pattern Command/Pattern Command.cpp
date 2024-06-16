#include <iostream>
#include<vector>
using namespace std;
class Command
{
public:
    virtual ~Command(){}
    virtual void Execute() = 0;
    virtual void UnDo() = 0;
}; 

class Barmen{
    vector<string> order;
    vector<string> finished_orders;
public: 
    Barmen() {}
    
    ~Barmen(){}

    void Cook() {   
        for(int i = 0; i < order.size(); i++) {
            cout << order[i] << " cooking\n";
            finished_orders.push_back(order[i]);
        }
    }

    void Speak() {
        cout << "bla bla\n";
    }

    void Reverse() {
        if (finished_orders.empty())
            return;
        finished_orders.pop_back();
    }

    void SetOrder(vector<string> order) {
        this->order = order;
    }

    vector<string> GetOrder() {
        return order;
    }
};

class CookingCommand : public Command {
    Barmen* barmen;
    string dish;
public:

    CookingCommand(Barmen* barmen) : barmen(barmen){}

    ~CookingCommand(){}

    void Execute() override {
        barmen->Cook();
    }

    void UnDo() override {
        barmen->Reverse();
    }
};

class SpeakCommand : public Command{
    Barmen* barmen;
public:

    SpeakCommand(Barmen* barmen) : barmen(barmen){}

    ~SpeakCommand(){}

    void Execute() override {
        barmen->Speak();
    }

    void UnDo() override {
        cout << "...\n";
    }
};

class CommandHistory {
    vector<Command*> command_history;
public:
    CommandHistory(){}

    ~CommandHistory() {
        for (Command* current : command_history)
            delete current;
    }
    void Add(Command* command) {
        command_history.push_back(command);
    }

    void Delete(Command* command) {
        if(!command_history.empty()) {
            for (int i = 0; i < command_history.size(); i++) {
                if (command_history[i] == command)
                    command_history.erase(command_history.begin() + i);
            }
        }
        return;
    }

    int GetSize() {
        return command_history.size();
    }
};
class Waiter {
    Barmen* barmen;
    vector<string> order;
    CommandHistory* history;
    Command* ChooseCommand(string order) {
        if (order == "speak") {
            return new SpeakCommand(barmen);
        }
        else if (order == "cook") {
            return new CookingCommand(barmen);
        }   
        return nullptr;
    }
public:
    Waiter(Barmen* barmen) : barmen(barmen) {
        history = new CommandHistory;
    }

    ~Waiter() {}

    void SetOrder() {
        string answer;
        cout << "What do you want from our menu?\n";
        while (true) {            
            cin >> answer;
            order.push_back(answer);
            cout << "Something else?\n";
            cin >> answer;
            if (answer == "yes")
                continue;
            else
                break;
        }
    }

    vector<string> GetOrder() {
        return order;
    }

    void DoWork() {
        
        Menu();
        Command* command = nullptr;
        int number = 0/*rand() % 2*/;
        SetOrder();
        barmen->SetOrder(GetOrder());
        if (number == 0) {
            command = ChooseCommand("speak");
            command->Execute();
            command->UnDo();
            history->Add(command);
        }
        command = ChooseCommand("cook");
        command->Execute();
        history->Add(command);

    }
    void Menu() {
        cout << "\t\t:Menu:\n";
        cout << "\tSprite\n";
        cout << "\tFanta\n";
        cout << "\tPepsi\n";
        cout << "\tSomething what you want\n";
    }
};

int main()
{
    srand(time(0));
    Waiter braun(new Barmen());
    braun.DoWork();
    //auto p = braun.GetOrder();
    
    
}
