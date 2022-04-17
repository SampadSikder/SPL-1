struct stack
{
    int index = -1;
    int capacity = N;
    double array[N];

    void push(double value)
    {

        if (index == capacity)
        {
            return;
        }

        index++;
        array[index] = value;
    }
    double pop()
    {
        if (index == -1)
        {
            return 0;
        }
        double value = array[index];
        index--;
        return value;
    }
    double top()
    {
        if (index != -1)
        {
            return array[index];
        }
        else
        {
            return 0;
        }
    }
    int size()
    {
        return index + 1;
    }
} stck;