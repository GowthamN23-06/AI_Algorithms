#include<iostream>
#include<vector>
#include<array>
#include<exception>
#include<variant>
using namespace std;
using st1 = string;

int x = 0;
template <typename T>
//void merge(vector<int> & arr, int left, int middle, int right)
void merge(vector<T> & arr, int left, int middle, int right)
{
    int n1 = middle -left + 1;
    int n2 = right - middle;

    vector<T> L(n1);
    vector<T> R(n2);

    for(int i=0; i<n1; i++)
        L[i] = arr[left + i];
    for(int j=0; j<n2; j++)
        R[j] = arr[middle + 1 + j];

    int i =0, j= 0, k = left ;
    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {+
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }  
    while(j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

}

template <typename T>
//void mergeSort(vector<int> & arr, int left, int right)
void mergeSort(vector<T> & arr, int left, int right)
{
    if(left >=right)
    {
        return;
    }
    
        int middle = left + (right - left) / 2;

        x++;
        cout<<"Iteration"<<x<<endl;
        cout<<"Left: "<<left<<" Middle: "<<middle<<" Right: "<<right<<endl;

        for(int i =0; i< right; i++)
            cout<<arr[i]<<" ";

        cout<<endl<<endl;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);

     
    
}



int main()
{
    unsigned int a =1;

    //vector<int> arr = {49, 27, 43, 10, 12, 5, 8, 19, 6, 3};
    vector<float> arr = {49.1, 27.2, 43.8, 10.9, 12.01, 5.1, 12.05, 19, 6, 3};
    int n = arr.size();

    mergeSort(arr, 0, n - 1);

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;

    st1 st2, st3;
    st2 = {"Little Endian"};
    st3 = {"Big Endian"};

    if(*(char *)&a ==1)
        cout << st2<< endl;
    else
        cout << st3 << endl;

    char const *p = st3.c_str();

    cout<<p<<endl;


    int x, y;
    x = 200;
    y = 300;


    array<int,10> arr2 = {0};

    cout<<arr2[0]<<endl;

    arr2[0] = 10;

    cout<<arr2[0]<<endl;



    return 0;

}