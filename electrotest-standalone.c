#include "electrotest-standalone.h"

float calc_power_i(float volt, float current)
{
    return volt * current;
}

float calc_power_r(float volt, float resistance)
{
    return volt * volt / resistance;
}

float calc_resistance(int count, char conn, float *array)
{

    if (count <= 0)
    {
        return -1;
    }

    // resistans för seriekoppling
    if (conn == 'S' || conn == 's')
    {
        int total_res1 = 0;
        for (int i = 0; i < count; i++)
        {
            total_res1 += array[i];
        }

        return total_res1;
    }

    // resistans för paralellkoppling
    if (conn == 'P' || conn == 'p')
    {
        float total_res2 = 0;
        for (int i = 0; i < count; i++)
        {
            if (array[i] < 1)
            {
                return 0;
            }

            total_res2 += 1 / array[i];
        }

        total_res2 = 1 / total_res2;

        return total_res2;
    }

    return -1;
}

const float E12[] = {
    8200, 6800, 5600, 4700, 3900, 3300, 2700, 2200, 1800, 1500, 1200, 1000,
    820, 680, 560, 470, 390, 330, 270, 220, 180, 150, 120, 100,
    82, 68, 56, 47, 39, 33, 27, 22, 18, 15, 12, 10,
    8.2, 6.8, 5.6, 4.7, 3.9, 3.3, 2.7, 2.2, 1.8, 1.5, 1.2, 1.0};

bool backtrack(int start, float target, float sum, float *res_array, int count, int *res_count)
{

    if (target == sum)
    {
        *res_count = count;
        return true;
    }

    if (sum > target || start >= sizeof(E12) / sizeof(E12[0]) || count >= 3)
    {
        return false;
    }

    res_array[count] = E12[start];

    if (E12[start] == target)
    {
        *res_count = 1;
        res_array[0] = target;
        res_array[1] = 0;
        res_array[2] = 0;
        return true;
    }

    if (backtrack(start, target, sum + E12[start], res_array, count + 1, res_count))
    {
        return true;
    }

    if (backtrack(start + 1, target, sum, res_array, count, res_count))
    {
        return true;
    }

    res_array[count] = 0;
    return false;
}

int e_resistance(float orig_resistance, float *res_array)
{

    if (fabs(orig_resistance) < FLT_EPSILON)
    {
        for (int i = 0; i < 3; i++)
            res_array[i] = 0;
        return 0;
    }

    int res_count = 0;
    backtrack(0, orig_resistance, 0, res_array, 0, &res_count);

    return res_count;
}

int main(int argc, char const *argv[])
{

    float volt;
    float totres;   // total resistance
    float *compres; // componentresistance
    float res;      // resistance
    float cur;      // current
    float *floatsp;
    int components = 0;
    int count;
    char conn; // Connection, S or P
    float *e12_resulting_array;

    e12_resulting_array = (float *)malloc(3 * sizeof(float));

    printf("Ange spänningskälla i V: ");
    scanf("%f", &volt);
    getchar();

    printf("Ange koppling [S | P]: ");
    scanf("%c", &conn);

    printf("Ange antalet komponenter: ");
    scanf("%d", &count);

    if (count < 1)
    {
        printf("Inget giltigt antal komponenter! \n");
        return 1;
    }

    compres = (float *)malloc(count * sizeof(float));

    for (int i = 0; i < count; i++)
    {
        printf("Komponent %d i ohm: ", i + 1);
        scanf("%f", &compres[i]);
    }

    totres = calc_resistance(count, conn, compres);
    printf("Ersättningsresistansen är:\n%.1f ohm\n", totres);

    if (components == "R" || "r")
    {
        cur = volt / totres;
        if (calc_power_i(volt, cur) == calc_power_r(volt, res))
        {
            printf("Effekten är: 5.2f W\n", calc_power_i(volt, cur));
        }
    }

    int e12_components_used = e_resistance(totres, e12_resulting_array);
    printf("Ersättningsresistans:\n");
    for (int i = 0; i < e12_components_used; i++)
    {
        printf("%.1f\n", e12_resulting_array[i]);
    }
}