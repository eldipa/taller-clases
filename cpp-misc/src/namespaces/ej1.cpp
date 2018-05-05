#include <vector>
#include <algorithm>

// Descomentar `using ...` provoca ambigüedad ya que count es una
// variable global en <algorithm> 
// En caso de descomentar using namespace
// Se puede desambiguar escribiendo `::count++` para referirse al local
// y std::count para referirse al de <algorithm>

//using namespace std;


int count = 0;

int main (int argc, char** argv) {
  std::vector<int> v{1,2,3,1,2,1};
  std::sort(v.begin(), v.end());
  for (unsigned int i = 0; i < v.size(); ++i) {
    if (v[i] == 1) {
        count++;
    } else {
      break;
    }
  }
  return 0;
}