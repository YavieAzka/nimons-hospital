# Rencana Implementasi ADT dan Materi

## ADT Sederhana

Digunakan untuk menyimpan data pasien, dokter, manager, dsb.

```
typedef struct { ...
} Pasien;
```

## ADT List

Digunakan untuk menyimpan daftar user dan dapat berupa array dinamis.

```
User users[MAX_USER];
```

## ADT Linked List

Digunakan untuk melakukan pencarian dan pengurutan pada data.

```
typedef struct Node*
NodeAddress;
```

## ADT Matriks

Digunakan untuk tampilan denah rumah sakit.

```
Room matrix[MAX_ROW][MAX_COL];
```

## ADT Set

Digunakan untuk validasi username unik menggunakan hashset berbasis array dalam login/register.

## ADT Map

Digunakan untuk mendata penyakit dan dan list obat yang dapat menyembuhkannya.

```
Map<String, List<int>>
```

## ADT Stack

Digunakan untuk mendata obat yang terdapat di dalam perut pasien, untuk fitur minum obat dan penawar.

```
typedef struct Stack { ...
} Stack;
```

## ADT Queue

Digunakan untuk menyimpan data antrian pasien.

```
typedef struct Queue { ...
} Queue;
```

## File Eksternal

Load/Save dari .csv dan config.txt.

## Fungsi dan Prosedur

Digunakan untuk membagi setiap fungsi/prosedur dalam berbagai operasi.

## Array Search, Sort, Filter

Digunakan dalam beberapa modul yang mengharuskan data di sort.
