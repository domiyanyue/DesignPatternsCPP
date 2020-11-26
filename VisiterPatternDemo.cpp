// In object-oriented programming and software engineering,
// the visitor design pattern is a way of separating an algorithm from an
// object structure on which it operates. A practical result of this
// separation is the ability to add new operations to existing object
// structures without modifying the structures. It is one way to follow
// the open/closed principle.

#include <iostream>

class VisitorInterface;
class VisitableInterface {
  public:
    virtual double accept(const VisitorInterface &visitor) = 0;
};

class Liquor : public VisitableInterface {
  private:
    double price;

  public:
    Liquor(double p) : price{p} {}
    double getPrice() const { return price; }
    double accept(const VisitorInterface &visitor);
};

class Tobacco : public VisitableInterface {
  private:
    double price;

  public:
    Tobacco(double p) : price{p} {}
    double getPrice() const { return price; }
    double accept(const VisitorInterface &visitor);
};

class Necessity : public VisitableInterface {
  private:
    double price;

  public:
    Necessity(double p) : price{p} {}
    double getPrice() const { return price; }
    double accept(const VisitorInterface &visitor);
};

// visitor
class VisitorInterface {
  public:
    virtual double visit(const Liquor &liquorItem) const = 0;
    virtual double visit(const Tobacco &tobaccoIterm) const = 0;
    virtual double visit(const Necessity &necessityItem) const = 0;
};

class TaxVisitor : public VisitorInterface {
  public:
    double visit(const Liquor &liquorItem) const {
        double price = liquorItem.getPrice() * 1.18;
        std::cout << "Liquor Item Price with Tax: " << price << "\n";
        return price;
    }

    double visit(const Tobacco &tobaccoIterm) const {
        double price = tobaccoIterm.getPrice() * 1.32;
        std::cout << "Tobacco Item Price with Tax: " << price << "\n";
        return price;
    }

    double visit(const Necessity &necessityItem) const {
        double price = necessityItem.getPrice() * 1.0;
        std::cout << "Necessity Item Price with Tax: " << price << "\n";
        return price;
    }
};

class TaxHolidyVisitor : public VisitorInterface {
  public:
    double visit(const Liquor &liquorItem) const {
        double price = liquorItem.getPrice() * 1.10;
        std::cout << "Liquor Item Price with Tax: " << price << "\n";
        return price;
    }

    double visit(const Tobacco &tobaccoIterm) const {
        double price = tobaccoIterm.getPrice() * 1.30;
        std::cout << "Tobacco Item Price with Tax: " << price << "\n";
        return price;
    }

    double visit(const Necessity &necessityItem) const {
        double price = necessityItem.getPrice() * 1.0;
        std::cout << "Necessity Item Price with Tax: " << price << "\n";
        return price;
    }
};

double Liquor::accept(const VisitorInterface &visitor) {
    return visitor.visit(*this);
}

double Tobacco::accept(const VisitorInterface &visitor) {
    return visitor.visit(*this);
}

double Necessity::accept(const VisitorInterface &visitor) {
    return visitor.visit(*this);
}

int main() {
    TaxVisitor taxcalc;
    TaxHolidyVisitor taxcalcHoliday;

    Necessity milk(3.00);
    Liquor vodka(11.99);
    Tobacco cigar(12.00);

    std::cout << milk.accept(taxcalc) << "\n";
    std::cout << vodka.accept(taxcalc) << "\n";
    std::cout << cigar.accept(taxcalc) << "\n";

    std::cout << milk.accept(taxcalcHoliday) << "\n";
    std::cout << vodka.accept(taxcalcHoliday) << "\n";
    std::cout << cigar.accept(taxcalcHoliday) << "\n";

    return 0;
}