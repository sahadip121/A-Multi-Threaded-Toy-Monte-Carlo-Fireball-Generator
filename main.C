#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

// Phase 1: Abstract Base Class
class Particle {
public:
    // Virtual destructor is crucial for inheritance
    virtual ~Particle() = default; 

    // Pure virtual functions that derived classes MUST implement
    virtual double GetPt() const = 0;
    virtual double GetPz() const = 0;
    virtual double GetEnergy() const = 0;
    
    // An implemented method using the virtual ones
    double GetRapidity() const {
        double E = GetEnergy();
        double pz = GetPz();
        return 0.5 * std::log((E + pz) / (E - pz));
    }
};

// Phase 1.5: The Derived Class
class Pion : public Particle {
private:
    double px, py, pz, E;
public:
    Pion(double px_in, double py_in, double pz_in, double E_in) 
        : px(px_in), py(py_in), pz(pz_in), E(E_in) {}

    double GetPt() const override {
        return std::sqrt(px*px + py*py);
    }
    double GetPz() const override { return pz; }
    double GetEnergy() const override { return E; }
};

// Phase 2: The Event Manager
class Event {
private:
    // Using smart pointers: Memory automatically cleans up when Event is destroyed!
    std::vector<std::unique_ptr<Particle>> particles;

public:
    // We must pass the unique_ptr by moving it, transferring ownership
    void AddParticle(std::unique_ptr<Particle> p) {
        particles.push_back(std::move(p));
    }

    size_t GetMultiplicity() const {
        return particles.size();
    }
};