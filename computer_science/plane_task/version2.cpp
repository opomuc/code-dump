#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

int oiltime = 500;
int qpoint = 10;

class Raptor
{
    int data_[50];
    int from_x;
    int from_y;
    int to_x;
    int to_y;
    int point_num;
    int curr_x;
    int curr_y;
    int arrival_time;


    public:

    int velocity;
    int distance;
    int boost_size;
    int boost_[50];

    Raptor();
    ~Raptor();
    void put_point_num(int num);
     int get_point_num();
    void change_from(int x, int y);
    void change_curr(int x, int y);
    void change_to(int x, int y);
     int get_curr_x();
     int get_curr_y();
     int get_from_x();
     int get_from_y();
     int get_to_x();
     int get_to_y();
     int min_dist();
    void read_data(FILE* in);
     int get_data(int num);
    void move_();
    void delete_point(int this_, int that_);
     int distance_to_go();
     int distance_to_base();
    void boost_collect(FILE* in);
    void add_point(int num, int boost_num);
};

Raptor::Raptor():
    from_x (0),
    from_y (0),
    to_x (0),
    to_y (0),
    point_num (0),
    curr_x (0),
    curr_y (0),
    arrival_time (0),
    velocity (20),
    distance (0),
    boost_size (0)
{
    memset(data_, 0, sizeof(int));
    memset(boost_, 0, sizeof(int));
    printf("\nI'm a constructor. I made a raptor");
}

Raptor::~Raptor()
{
    printf("\nI'm a destructor. I crushed the raptor");
}

void Raptor::put_point_num(int num)
{
    point_num = num;
}

int Raptor::get_point_num()
{
    return point_num;
}

void Raptor::change_from(int x, int y)
{
    from_x = x;
    from_y = y;
}

void Raptor::change_to(int x, int y)
{
    to_x = x;
    to_y = y;
}

void Raptor::change_curr(int x, int y)
{
    curr_x = x;
    curr_y = y;
}

int Raptor::get_curr_x()
{
    return curr_x;
}

int Raptor::get_curr_y()
{
    return curr_y;
}

int Raptor::get_from_x()
{
    return from_x;
}

int Raptor::get_from_y()
{
    return from_y;
}

int Raptor::get_to_x()
{
    return to_x;
}

int Raptor::get_to_y()
{
    return to_y;
}

int Raptor::min_dist()
{
    int min_d = 9999999;
    int dist = 0;

    for (int i = 0, k = 0; i < point_num; i++, k = i*2)
    {
        dist = (curr_x - data_[k])*(curr_x - data_[k]) + (curr_y - data_[k+1])*(curr_y - data_[k+1]);

        if (dist < min_d)
        {
            min_d = dist;
            to_x = data_[k];
            to_y = data_[k+1];
            data_[39] = k;
            data_[40] = k+1;
        }

    }

    arrival_time = sqrt(min_d) / velocity;
    distance = sqrt(min_d);

    return sqrt(min_d);
}

void Raptor::read_data(FILE* in)
{
    int j = 0;

    do
    {
        for (int i = 0; i < 2; i++)
        {
            fscanf(in, "%d ", &data_[j]);
            data_[j] *= 10;
            j++;
        }
        point_num++;
    }
    while (!feof(in));
}

int Raptor::get_data(int num)
{
    return data_[num];
}

void Raptor::move_()
{
    curr_x = curr_x - (velocity * (curr_x - to_x) / distance);
    curr_y = curr_y - (velocity * (curr_y - to_y) / distance);
}

void Raptor::delete_point(int this_, int that_)
{
    data_[this_] = data_[that_];
    data_[this_ + 1] = data_[that_ + 1];
}

int Raptor::distance_to_go()
{
    return sqrt((from_x - to_x)*(from_x - to_x) + (from_y - to_y)*(from_y - to_y));
}

int Raptor::distance_to_base()
{
    return sqrt(curr_x * curr_x + curr_y * curr_y);
}

void Raptor::boost_collect(FILE* in)
{
    int j = 1;
    do
    {
        fscanf(in, "%d ", &boost_[j]);

        if (j % 3 != 0)
        {
            boost_[j] *= 10;
        }

        j++;
    }
    while (!feof(in));

    boost_size = j/3;
}

void Raptor::add_point(int num, int boost_num)
{
    data_[num * 2] = boost_[boost_num*3 - 2];
    data_[num * 2 + 1] = boost_[boost_num*3 - 1];
    point_num++;
}


int main()
{
    FILE* income = fopen("navy.txt", "r");
    FILE* output = fopen("out.txt", "w");
    FILE* fire = fopen("fire.txt", "r");
    FILE* trace = fopen("travel.txt", "w");

    Raptor plane;

    plane.read_data(income);
    plane.boost_collect(fire);

    int distance_ = 0, n = 0, dx = 0, dy = 0;

    for (int time = 0; time < oiltime; time++)
    {
        for (int l = 1; l <= plane.boost_size; l++)
        {
            n = l*3;
            if (time == plane.boost_[n])
            {
                plane.add_point(plane.get_point_num(), l);
            }
        }

        distance_ = plane.min_dist();

        if (distance_ < 20)
        {
            distance_ = plane.distance_to_go();

            dx = (plane.get_from_x() - plane.get_to_x()) * plane.velocity / distance_;
            dy = (plane.get_from_y() - plane.get_to_y()) * plane.velocity / distance_;

            fprintf(output, "\nfrom: (%d,%d);  to: (%d,%d);  target: (%d,%d);  current time: %d;  dx = %d;  dy = %d;", plane.get_from_x(), plane.get_from_y(), plane.get_curr_x(), plane.get_curr_y(), plane.get_to_x(), plane.get_to_y(), time, dx, dy);

            plane.change_from(plane.get_curr_x(), plane.get_curr_y());

            int num = plane.get_point_num();

            int val = (num - 1)*2;

            plane.delete_point(plane.get_data(39), val);

            plane.put_point_num(--num);

            n++;
        }
        else
        {
            int k1 = plane.distance_to_base() / plane.velocity;
//            int k2 = plane.distance_to_go() / plane.velocity;

            if (k1 > (oiltime - 4 - time))
            {
                time += k1;

                fprintf(output, "\ncurrent time: %d    Returned to base\nPoints that were not reached:", time);

                for (int i = 0; i < plane.get_point_num(); i++)
                {
                    k1 = i * 2;
                    fprintf(output, "\nx = %d, y = %d", plane.get_data(k1), plane.get_data(k1+1));
                }

                break;
            }
            else
            {
                plane.move_();
                fprintf(trace, "%d %d\n", plane.get_curr_x(), plane.get_curr_y());
            }
        }

        if (plane.get_point_num() == 0)
        {
            break;
        }

    }

    fclose(trace);
    fclose(fire);
    fclose(output);
    fclose(income);
    return 0;
}
