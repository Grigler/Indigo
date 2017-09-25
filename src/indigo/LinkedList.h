#ifndef __IND_LINKED_LIST__
#define __IND_LINKED_LIST__

#include <memory>

//TODO - I know I've set this up wrong for recursion but I'm not doing it properly yet

namespace Indigo
{

  class GameObj;

  struct Item
  {
    Item *next;
    std::shared_ptr<GameObj> gameObj;
  };

  class LinkedList
  {
  public:
    void Add(std::shared_ptr<GameObj> _gameObj);

    void Remove(std::shared_ptr<GameObj> _gameObj);
    void Remove(Item *_item);

    int GetSize() { return size; }

  private:
    Item *root;

    int size;

  };

} //End of namespace

#endif