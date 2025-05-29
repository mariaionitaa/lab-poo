#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "service.h"
#include "employee.h"
#include "client.h"
#include "appointment.h"
#include "schedule.h"
#include "product.h"

using namespace Beauty_Salon;

// Functia pentru adaugarea datelor demonstrative in sistem, Populeaza sistemul cu servicii, angajati, clienti si produse
void PopulateWithDemoData(
    std::vector<std::unique_ptr<Service>>& services,
    std::vector<std::unique_ptr<Employee>>& employees,
    std::vector<Client>& clients,
    std::vector<std::unique_ptr<Product>>& products,
    Schedule& schedule) {
    
    // Adaugare servicii - folosind unique_ptr cu new
    services.push_back(std::unique_ptr<Service>(new HairService("Tuns", 30.0, true, true)));
    services.push_back(std::unique_ptr<Service>(new HairService("Vopsit", 80.0, true, false)));
    services.push_back(std::unique_ptr<Service>(new NailService("Manichiura", 25.0, false, 10)));
    services.push_back(std::unique_ptr<Service>(new NailService("Pedichiura", 35.0, true, 10)));
    services.push_back(std::unique_ptr<Service>(new SpaService("Masaj Relaxare", 50.0, false, false)));
    services.push_back(std::unique_ptr<Service>(new SpaService("Tratament Facial Premium", 75.0, true, true)));
    
    // Adaugare angajati
    std::unique_ptr<Employee> stylista(new Stylist("Ana Maria", 25.0, true, 5));
    std::unique_ptr<Employee> stylistb(new Stylist("Ioana", 20.0, false, 2));
    std::unique_ptr<Employee> techniciana(new Technician("Elena", 22.0, true));
    std::unique_ptr<Employee> technicianb(new Technician("Mihai", 22.0, true));
    
    // Adaugare certificari pentru tehnicieni
    static_cast<Technician*>(techniciana.get())->AddCertification("Nail Art Specialist");
    static_cast<Technician*>(technicianb.get())->AddCertification("Spa Specialist");
    static_cast<Technician*>(technicianb.get())->AddCertification("Massage Therapist");
    
    employees.push_back(std::move(stylista));
    employees.push_back(std::move(stylistb));
    employees.push_back(std::move(techniciana));
    employees.push_back(std::move(technicianb));
    
    // Adaugare clienti
    clients.push_back(Client("Andrei", "0722123456", "andrei@email.com"));
    clients.push_back(Client("Maria", "0733234567"));
    clients.push_back(Client("Laura", "0744345678", "laura@email.com"));
    
    // Simulam vizite anterioare pentru un client VIP
    for (int i = 0; i < 10; i++) {
        clients[0].AddVisit();
    }
    
    // Adaugare produse
    products.push_back(std::unique_ptr<Product>(new RetailProduct("Sampon Revitalizant", "BrandX", 15.0, ProductCategory::HAIR_CARE, 0.4)));
    products.push_back(std::unique_ptr<Product>(new RetailProduct("Balsam Nutritiv", "BrandX", 12.0, ProductCategory::HAIR_CARE, 0.4)));
    products.push_back(std::unique_ptr<Product>(new RetailProduct("Crema Hidratanta", "SkinY", 25.0, ProductCategory::SKIN_CARE, 0.5)));
    products.push_back(std::unique_ptr<Product>(new ProfessionalProduct("Vopsea profesionala", "ColorPro", 30.0, ProductCategory::HAIR_CARE, "SupplierZ")));
    products.push_back(std::unique_ptr<Product>(new ProfessionalProduct("Ulei de masaj", "MassageX", 20.0, ProductCategory::SKIN_CARE, "SupplierW")));
    
    // Actualizam stocul produselor
    for (auto& product : products) {
        product->UpdateStock(10); // Adaugam 10 bucati din fiecare produs
    }
    
    // Crearea unor programari
    TimeSlot slot1(10, 0, 60); // 10:00, 60 minute
    TimeSlot slot2(14, 30, 45); // 14:30, 45 minute
    
    Appointment app1(clients[0], employees[0].get(), services[0].get(), slot1);
    Appointment app2(clients[1], employees[2].get(), services[2].get(), slot2);
    
    // Adaugam programarile in sistem
    schedule.AddAppointment(app1);
    schedule.AddAppointment(app2);
}

// Functia pentru afisarea meniului principal
void DisplayMainMenu() {
    std::cout << "\n=== SALON DE INFRUMUSETARE - SISTEM DE MANAGEMENT ===\n";
    std::cout << "1. Gestionare Servicii\n";
    std::cout << "2. Gestionare Angajati\n";
    std::cout << "3. Gestionare Clienti\n";
    std::cout << "4. Gestionare Programari\n";
    std::cout << "5. Gestionare Produse\n";
    std::cout << "6. Rapoarte si Statistici\n";
    std::cout << "0. Iesire\n";
    std::cout << "Alegere: ";
}

// Functia pentru afisarea tuturor serviciilor disponibile
void DisplayAllServices(const std::vector<std::unique_ptr<Service>>& services) {
    std::cout << "\n=== SERVICII DISPONIBILE ===\n";
    if (services.empty()) {
        std::cout << "Nu exista servicii inregistrate.\n";
        return;
    }
    
    for (size_t i = 0; i < services.size(); ++i) {
        std::cout << i + 1 << ". " << *services[i] << std::endl;
    }
}

// Functia pentru afisarea tuturor angajatilor
void DisplayAllEmployees(const std::vector<std::unique_ptr<Employee>>& employees) {
    std::cout << "\n=== ANGAJATI ===\n";
    if (employees.empty()) {
        std::cout << "Nu exista angajati inregistrati.\n";
        return;
    }
    
    for (size_t i = 0; i < employees.size(); ++i) {
        std::cout << i + 1 << ". " << *employees[i] << std::endl;
    }
}

// Functia pentru afisarea tuturor clientilor
void DisplayAllClients(const std::vector<Client>& clients) {
    std::cout << "\n=== CLIENTI ===\n";
    if (clients.empty()) {
        std::cout << "Nu exista clienti inregistrati.\n";
        return;
    }
    
    for (size_t i = 0; i < clients.size(); ++i) {
        std::cout << i + 1 << ". " << clients[i] << std::endl;
    }
}

// Functia pentru afisarea tuturor produselor
void DisplayAllProducts(const std::vector<std::unique_ptr<Product>>& products) {
    std::cout << "\n=== PRODUSE ===\n";
    if (products.empty()) {
        std::cout << "Nu exista produse inregistrate.\n";
        return;
    }
    
    for (size_t i = 0; i < products.size(); ++i) {
        std::cout << i + 1 << ". " << *products[i] << std::endl;
    }
}

// Functia pentru demonstrarea operatorilor supraincarcati
void DemonstrateOperators(const std::vector<std::unique_ptr<Service>>& services, 
                         const std::vector<std::unique_ptr<Product>>& products) {
    std::cout << "\n=== DEMONSTRARE OPERATORI SUPRAINCARC ===\n";
    
    if (services.size() >= 2) {
        std::cout << "\nCombinare servicii folosind operatorul +:\n";
        ServicePackage package = *services[0] + *services[1];
        std::cout << package << std::endl;
        package.DisplayPackageInfo();
    }
    
    if (products.size() >= 2) {
        std::cout << "\nCombinare produse folosind operatorul +:\n";
        ProductBundle bundle = *products[0] + *products[1];
        std::cout << bundle << std::endl;
        bundle.DisplayBundleInfo();
    }
}

// Functia principala a programului
int main() {
    // Colectii pentru stocarea datelor - folosim obiecte pe heap
    std::vector<std::unique_ptr<Service>> services;
    std::vector<std::unique_ptr<Employee>> employees;
    std::vector<Client> clients;  // Clientii sunt pe stack 
    std::vector<std::unique_ptr<Product>> products;
    Schedule schedule(9, 20, 5); // Program 9-20, max 5 programari simultane
    
    // Populam sistemul cu date demo
    PopulateWithDemoData(services, employees, clients, products, schedule);
    
    int choice = -1;
    
    // Bucla principala a programului
    while (choice != 0) {
        DisplayMainMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: // Gestionare Servicii
                DisplayAllServices(services);
                break;
                
            case 2: // Gestionare Angajati
                DisplayAllEmployees(employees);
                break;
                
            case 3: // Gestionare Clienti
                DisplayAllClients(clients);
                break;
                
            case 4: // Gestionare Programari
                schedule.DisplayAllAppointments();
                break;
                
            case 5: // Gestionare Produse
                DisplayAllProducts(products);
                break;
                
            case 6: // Rapoarte si Statistici
                // Afisam raportul pentru ora 10 (ora primei programări)
                schedule.GenerateDailyReport(10);
                
                // Demonstram functionalitatea operatorilor supraincarcati
                DemonstrateOperators(services, products);
                break;
                
            case 0:
                std::cout << "La revedere!\n";
                break;
                
            default:
                std::cout << "Optiune invalida. Incercati din nou.\n";
                break;
        }
    }
    
    return 0;
} 
