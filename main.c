/*
 * Calculadora de bases numéricas
 * By: Lucas Eduardo Wendt
 * A ideia é calcular qualquer base até a 36
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

// Obtem o valor correspondente a um char. Ex A é 10, B é 11
int decode_char(char c) {
    //printf("%i\n", c);
    if (c >= 48 && c <= 57) { // Números
        return (int)c - 48;
    }
    if (c >= 65 && c <= 90) { // Letras maiúsculas
        return (int)c - 65 + 10;
    }
    if (c >= 97 && c <= 122) { // Letras minúsculas
        return (int)c - 97 + 10;
    }
    return 255;
}

// Transforma o valor de base 10 a char
char encode_char(int v) {
    if (v < 10) {
        return (char)(v + 48);
    } else {
        return (char)(v - 10 + 65);
    }
    return '_';
}

// printa o valor codificado
void encode_base(long int dec, int baseout) {
    if (dec >= baseout) {
        encode_base(dec / baseout, baseout);
    }
    printf("%c", encode_char(dec%baseout));
}

// Calcula a potência de números inteiros
long int ipow(int base, int exp) {
    long int res = 1;
    for (; exp > 0; exp--) {
        res *= base;
    }
    return res;
}

// decode_base: transforma o valor em string num long int para ser codificado na base de destino
long int decode_base(char* source, int basein) {
    if (source[0]  == '\0') return 0;
    int n = decode_char(source[0]);
    if (n >= basein) {
        printf("Valores inválidos de entrada encontrados: %c.\nO resultado será prejudicado.\n", source[0]);
    };
    long int res = decode_base(source + 1, basein);
    res += ipow(basein, strlen(source) - 1) * n; // Adiciona o valor daquela posição
    return res;
}

// ========== TESTES ===============

void test_encode_char() {
    assert(encode_char(1) == '1');
    assert(encode_char(10) == 'A');
    assert(encode_char(15) == 'F');
    assert(encode_char(35) == 'Z');
}

void test_decode_base() {
    assert(decode_base("aa20", 16) == 43552);
    assert(decode_base("fffa", 16) == 65530);
    assert(decode_base("416", 8) == 270);
    assert(decode_base("1110", 2) == 14);
}

void test_decode_char() {
    assert(2 == decode_char('2'));
    assert(9 == decode_char('9'));
    assert(0 == decode_char('0'));
    assert(10 == decode_char('A'));
    assert(10 == decode_char('a'));
}

void test_ipow() {
    assert(ipow(2,2) == 4);
    assert(ipow(3,2) == 9);
    assert(ipow(4, 3) == 64);
}

void test() {
    test_ipow();
    test_decode_char();
    test_decode_base();
    test_encode_char();
    encode_base(43552, 16);
    printf("\n");
}

int main() {
#define ISBASEVALIDA(base) \
    if (base > 35) { \
        printf("E: Base inválida!\n"); \
        abort(); \
     }
    printf("Digite o número da base de origem: ");
    int basein;
    scanf("%i", &basein);
    ISBASEVALIDA(basein)
    printf("Digite o número da base de saída: ");
    int baseout;
    scanf("%i", &baseout);
    ISBASEVALIDA(baseout);
    printf("Pronto para digitar valores, pressione Ctrl+C para parar.\n");
    char entrada[50];
    while(1) {
        printf("Valor -> ");
        scanf("%49s", entrada);
        long int decoded = decode_base(entrada, basein);
        encode_base(decoded, baseout);
        printf("\n");
    }
}
