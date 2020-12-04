#include <iostream>
#include <memory> //std::unique_ptr
#include <string>
#include <vector>

class Command {
  public:
    virtual ~Command(){};
    virtual void Execute() const = 0;
};

class SimpleCommand : public Command {
  private:
    std::string pay_load_;

  public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load) {}
    void Execute() const override {
        std::cout
            << "Simple Command: See, I can do simple things like printing ("
            << this->pay_load_ << "\n";
    }
};

class Receiver {
  public:
    void DoSomething(const std::string &msg1) {
        std::cout << "Receiver: working on (" << msg1 << ".)\n";
    }

    void DoSomethingElse(const std::string &msg2) {
        std::cout << "Receiver: also working on (" << msg2 << ".)\n";
    }
};

class ComplexCommand : public Command {
  private:
    std::unique_ptr<Receiver> receiver_;
    std::string msg1_;
    std::string msg2_;

  public:
    ComplexCommand(std::unique_ptr<Receiver> &receiver, std::string msg1,
                   std::string msg2)
        : receiver_(std::move(receiver)), msg1_(msg1), msg2_(msg2) {}

    void Execute() const override {
        std::cout << "Complex Command: Complex stuff should be done by a "
                     "receiver object. \n";
        this->receiver_->DoSomething(msg1_);
        this->receiver_->DoSomethingElse(msg2_);
    }
};

class Invoker {
  private:
    std::unique_ptr<Command> on_start_;
    std::unique_ptr<Command> on_finish_;

  public:
    ~Invoker() {}

    void SetOnStart(std::unique_ptr<Command> &&command) {
        this->on_start_ = std::move(command);
    }

    void SetOnFinish(std::unique_ptr<Command> &&command) {
        this->on_finish_ = std::move(command);
    }

    void DoSomethingImportant() {
        std::cout
            << "Invoker: Does anybody want something done before I begin? \n";
        if (this->on_start_) {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: ... doing something really important ... \n";
        std::cout
            << "Invoker: Does anybody want something done after I finish? \n";
        if (this->on_finish_) {
            this->on_finish_->Execute();
        }
    }
};

int main() {
    //    Invoker* invoker = new Invoker;
    std::unique_ptr<Invoker> invoker = std::make_unique<Invoker>();
    invoker->SetOnStart(std::make_unique<SimpleCommand>("Say hi!"));
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();
    invoker->SetOnFinish(std::make_unique<ComplexCommand>(
        receiver, "Send email", "Save report"));
    invoker->DoSomethingImportant();
    return 0;
}