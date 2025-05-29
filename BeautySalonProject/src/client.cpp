#include "client.h"
#include <iostream>
#include <algorithm>

namespace Beauty_Salon {
    // Initializarea membrului static
    int Client::m_total_clients = 0;
    
    int Client::GetTotalClients() {
        return m_total_clients;
    }
    
    // Implementarea constructorilor
    Client::Client() 
        : m_name("Unknown"), m_phone(""), m_email(""), 
          m_visits(0), m_is_vip(false), m_loyalty_points(0.0) {
        m_total_clients++;
    }
    
    Client::Client(const std::string& name) 
        : m_name(name), m_phone(""), m_email(""), 
          m_visits(0), m_is_vip(false), m_loyalty_points(0.0) {
        m_total_clients++;
    }
    
    Client::Client(const std::string& name, const std::string& phone) 
        : m_name(name), m_phone(phone), m_email(""), 
          m_visits(0), m_is_vip(false), m_loyalty_points(0.0) {
        m_total_clients++;
    }
    
    Client::Client(const std::string& name, const std::string& phone, const std::string& email) 
        : m_name(name), m_phone(phone), m_email(email), 
          m_visits(0), m_is_vip(false), m_loyalty_points(0.0) {
        m_total_clients++;
    }
    
    Client::~Client() {
        m_total_clients--;
    }
    
    // Getteri si setteri
    std::string Client::GetName() const {
        return m_name;
    }
    
    std::string Client::GetPhone() const {
        return m_phone;
    }
    
    std::string Client::GetEmail() const {
        return m_email;
    }
    
    int Client::GetVisits() const {
        return m_visits;
    }
    
    bool Client::IsVIP() const {
        return m_is_vip;
    }
    
    double Client::GetLoyaltyPoints() const {
        return m_loyalty_points;
    }
    
    void Client::SetPhone(const std::string& phone) {
        m_phone = phone;
    }
    
    void Client::SetEmail(const std::string& email) {
        m_email = email;
    }
    
    void Client::SetVIP(bool isVip) {
        m_is_vip = isVip;
    }
    
    // Metodele pentru gestionarea vizitelor si a punctelor
    void Client::AddVisit() {
        m_visits++;
        
        // Verificam daca clientul poate deveni VIP (după 10 vizite)
        if (m_visits >= 10 && !m_is_vip) {
            m_is_vip = true;
        }
        
        // Adaugam puncte de loialitate pentru fiecare vizita (5 puncte)
        AddLoyaltyPoints(5.0);
    }
    
    void Client::AddLoyaltyPoints(double points) {
        if (points > 0) {
            m_loyalty_points += points;
        }
    }
    
    bool Client::UseLoyaltyPoints(double points) {
        if (points > 0 && points <= m_loyalty_points) {
            m_loyalty_points -= points;
            return true;
        }
        return false;
    }
    
    // Implementarea metodei din interfața IDiscountable
    double Client::ApplyDiscount(double amount) {
        // Discount bazat pe statut VIP si numar de vizite
        double discount = 0.0;
        
        if (m_is_vip) {
            discount += 10.0; // 10% pentru VIP
        }
        
        // Discount suplimentar bazat pe numarul de vizite (max 5%)
        discount += std::min(5.0, static_cast<double>(m_visits) * 0.5);
        
        // Aplicam discount-ul la suma
        return amount * (1.0 - discount / 100.0);
    }
    
    // Afisare informatii
    void Client::DisplayInfo() const {
        std::cout << "Client: " << m_name << std::endl;
        std::cout << "Phone: " << (m_phone.empty() ? "N/A" : m_phone) << std::endl;
        std::cout << "Email: " << (m_email.empty() ? "N/A" : m_email) << std::endl;
        std::cout << "Visits: " << m_visits << std::endl;
        std::cout << "Status: " << (m_is_vip ? "VIP" : "Regular") << std::endl;
        std::cout << "Loyalty Points: " << m_loyalty_points << std::endl;
    }
    
    // Supraincarcare operator <<
    std::ostream& operator<<(std::ostream& os, const Client& client) {
        os << client.m_name << " (" << (client.m_is_vip ? "VIP" : "Regular") 
           << ", " << client.m_visits << " visits)";
        return os;
    }
}
