#include "Node.hpp"

int main() {
    Node node("127.0.0.1", 9000);
    node.listen();
    return 0;
}
