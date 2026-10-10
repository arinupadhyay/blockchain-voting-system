#include <stdio.h>
#include <limits.h>

struct Result
{
    int sum;
    int start;
    int end;
};

/* Find maximum crossing subarray */
struct Result maxCrossingSum(int arr[], int low, int mid, int high)
{
    int leftSum = INT_MIN;
    int sum = 0;
    int maxLeft = mid;

    for (int i = mid; i >= low; i--)
    {
        sum = sum + arr[i];

        if (sum > leftSum)
        {
            leftSum = sum;
            maxLeft = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int maxRight = mid + 1;

    for (int i = mid + 1; i <= high; i++)
    {
        sum = sum + arr[i];

        if (sum > rightSum)
        {
            rightSum = sum;
            maxRight = i;
        }
    }

    struct Result result;

    result.sum = leftSum + rightSum;
    result.start = maxLeft;
    result.end = maxRight;

    return result;
}


/* Divide and Conquer */
struct Result maxSubarray(int arr[], int low, int high)
{
    /* Base case */
    if (low == high)
    {
        struct Result result;

        result.sum = arr[low];
        result.start = low;
        result.end = high;

        return result;
    }

    int mid = (low + high) / 2;

    /* Maximum subarray in left half */
    struct Result left = maxSubarray(arr, low, mid);

    /* Maximum subarray in right half */
    struct Result right = maxSubarray(arr, mid + 1, high);

    /* Maximum subarray crossing middle */
    struct Result cross = maxCrossingSum(arr, low, mid, high);

    /* Return maximum of the three */
    if (left.sum >= right.sum && left.sum >= cross.sum)
        return left;

    else if (right.sum >= left.sum && right.sum >= cross.sum)
        return right;

    else
        return cross;
}


int main()
{
    printf("AP25110010359\n");
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int n = sizeof(arr) / sizeof(arr[0]);

    struct Result result = maxSubarray(arr, 0, n - 1);

    printf("Maximum Subarray = {");

    for (int i = result.start; i <= result.end; i++)
    {
        printf("%d", arr[i]);

        if (i < result.end)
            printf(", ");
    }

    printf("}\n");

    printf("Maximum Sum = %d\n", result.sum);

    return 0;
}