#include <string>
#include <sstream>
#include <algorithm>
#include "Cluster.h"

using namespace Clustering;
namespace Clustering {

    LNode::LNode(const Point & newPoint, LNodePtr nextPtr):point(newPoint)
    {
        point=newPoint;
        next=nextPtr;
    }

    Clustering::Cluster::Cluster()
    {
        __size = 0;
        __points = nullptr;
    }


    int Clustering::Cluster::getSize() const
    {
        return __size;
    }

    Clustering::Cluster::Cluster(const Cluster & rhs):Cluster()
    {
        for (int count = 0; count < rhs.__size; count++)
            add(rhs[count]);
    }


    Cluster &Clustering::Cluster::operator=(const Cluster &rhs)
    {
        LNodePtr curr;

        if(this==&rhs)
            return *this;
        else
        {
            while (__points != nullptr) {
                curr = __points;
                __points = __points->next;
                delete curr;
                __size--;
            }

            for (int count = 0; count < rhs.__size; count++)
                add(rhs[count]);
        }

        return *this;
    }

    const Point &Cluster::operator[](unsigned int index) const
    {
        LNodePtr cursor=__points;
        for(int count =0; (count < index) && (cursor->next != nullptr); count++)
            cursor=cursor->next;
        return cursor->point;
    }

    Clustering::Cluster::~Cluster()
    {
        if(__points!=nullptr)
        {
            LNodePtr prev=__points;
            LNodePtr curr=nullptr;
            while (prev != nullptr)
            {
                curr = prev->next;
                delete prev;
                prev = curr;
            }
        }
    }

    void Clustering::Cluster::add(const Point &point)
    {
        LNodePtr insertPtr=new LNode(point, nullptr);
        LNodePtr curr=__points;
        LNodePtr prev=__points;

        if(__points==nullptr)
        {
            __points = insertPtr;
            __size++;
            return;
        }
        else if(__points->next==nullptr)
        {
            if(point<__points->point)
            {
                __points=insertPtr;
                insertPtr->next=prev;
                __size++;
                return;
            }
            else
            {
                __points->next=insertPtr;
                __size++;
                return;
            }
        }
        else
        {
            curr=curr->next;
            if(point < prev->point)
            {
                __points = insertPtr;
                insertPtr->next=prev;
                __size++;
                return;
            }
            while(curr!=nullptr)
            {
                if(point < curr->point)
                {
                    prev->next=insertPtr;
                    insertPtr->next=curr;
                    __size++;
                    return;
                }
                curr = curr->next;
                prev = prev->next;
            }
            prev->next=insertPtr;
            __size++;

        }
    }

    const Point &Clustering::Cluster::remove(const Point &point)
    {

        LNodePtr curr=__points;
        LNodePtr prev=__points;

        if(__points==nullptr)
            return point;
        else if(__points->point == point)
        {
            curr=__points;
            __points=__points->next;
            delete curr;
            __size--;
        }
        else
        {
            curr=curr->next;
            while (curr!= nullptr)
            {
                if (curr->point == point) {
                    prev->next=curr->next;
                    delete curr;
                    __size--;
                    break;
                }
                curr = curr->next;
                prev = prev->next;
            }
        }
        return point;
    }

    bool Clustering::Cluster::contains(const Point &point)
    {
        for (LNodePtr Cursor = this->__points; Cursor != nullptr; Cursor = Cursor->next)
        {
            if (Cursor->point == point){
                return true;
            }
        }
        return false;
    }

    bool operator==(const Cluster &c1, const Cluster &c2)
    {
        LNodePtr k1= c1.__points;
        LNodePtr k2=c2.__points;
        bool equal=true;
        if (c1.__size != c2.__size)
            equal=false;
        while(k1!=nullptr && k2!=nullptr)
        {
            if(k1->point!=k2->point)
                equal=false;
            k1=k1->next;
            k2=k2->next;
        }
        return equal;
    }

    bool operator!=(const Cluster &c1, const Cluster &c2)
    {
        return (!(c1==c2));
    }

    Cluster &Clustering::Cluster::operator+=(const Point &point)
    {
        add(point);
        return *this;
    }

    Cluster &Clustering::Cluster::operator-=(const Point &point)
    {
        remove(point);
        return *this;
    }

    const Cluster operator+(const Cluster & c1, const Point &point)
    {
        Cluster c2(c1);
        c2+= point;

        return c2;
    }

    const Cluster operator-(const Cluster & c1, const Point &point)
    {
        Cluster c2(c1);
        c2-= point;
        return c2;
    }

    Cluster &Clustering::Cluster::operator+=(const Cluster & c1)
    {

        for (int count = 0; count < c1.__size; count++)
        {
            if (!contains(c1[count]))
                add(c1[count]);
        }

        return *this;
    }

    Cluster &Clustering::Cluster::operator-=(const Cluster &c1)
    {
        for (int count = 0; count < c1.__size; count++)
            if (contains(c1[count]))
                remove(c1[count]);
        return *this;
    }
    const Cluster operator+(const Cluster &c1, const Cluster &c2)
    {
        Cluster k1(c1);
        k1+=c2;
        return k1;
    }
    const Cluster operator-(const Cluster &c1, const Cluster &c2)
    {
        Cluster k1(c1);
        k1-=c2;
        return k1;
    }
    std::ostream &operator<<(std::ostream &os, const Cluster &c1)
    {
        LNodePtr cursor=c1.__points;
        for(int count = 0; count < c1.__size; count++)
        {
            os << cursor->point << std::endl;
            cursor = cursor->next;
        }
        return os;
    }
    std::istream &operator>>(std::istream &input, Cluster &c1)
    {
        std::string line;
        getline(input,line);

        if (line.empty())
        {
            return input;
        }

        int count = std::count(line.begin(), line.end(), ',');
        Point ptr(count + 1);

        std::istringstream ss(line);
        ss >> ptr;

        c1.add(ptr);
        return input;
    }

}