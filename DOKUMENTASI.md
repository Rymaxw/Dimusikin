# Dokumentasi Program Music Player

## 1. Fitur Program

Program ini adalah aplikasi pemutar musik berbasis konsol yang memiliki dua peran utama: **User** dan **Admin**.

### Fitur User
- **Pemutaran Lagu**:
  - **Putar Lagu**: Memilih lagu berdasarkan ID atau Judul.
  - **Kontrol Playback**: Stop, Next Song, Previous Song.
  - **Auto-Play**: Otomatis memutar lagu selanjutnya berdasarkan *Genre* yang sama (jika dalam mode Library) atau urutan Playlist (jika dalam mode Playlist).
- **Pencarian Lagu**:
  - Pencarian berdasarkan **Judul**, **Artis**, dan **Genre**.
  - Mendukung pencarian *case-insensitive* (tidak membedakan huruf besar/kecil).
- **Manajemen Playlist**:
  - Membuat, Mengubah nama, dan Menghapus Playlist.
  - Menambahkan lagu ke dalam Playlist.
  - Memainkan lagu langsung dari Playlist.
- **Antrean & Riwayat**:
  - **Queue (Antrean)**: Menambahkan lagu ke antrean putar.
  - **History (Riwayat)**: Melihat riwayat lagu yang telah diputar dan fitur *Previous Song* yang mengambil dari riwayat.
- **Informasi Status**:
  - Menampilkan lagu yang sedang diputar ("NOW PLAYING") di bagian atas menu utama secara persisten.

### Fitur Admin
- **Manajemen Lagu (CRUD)**:
  - **Tambah Lagu**: Menambahkan lagu baru dengan detail (Judul, Artis, Genre, Tahun, Durasi).
  - **Edit Lagu**: Mengubah detail lagu yang sudah ada.
  - **Hapus Lagu**: Menghapus lagu dari sistem berdasarkan ID.
  - **Lihat Semua Lagu**: Menampilkan daftar seluruh lagu yang tersedia.

## 2. Struktur Data

Program ini mengimplementasikan berbagai struktur data linear untuk mengelola data secara efisien:

- **Doubly Linked List (`SongNode`)**:
  - Digunakan untuk menyimpan daftar utama lagu.
  - Memungkinkan navigasi dua arah (Next/Prev), meskipun traversal utama seringkali satu arah, struktur `prev` memudahkan potensi pengembangan fitur mundur.
  - *Struct*: `Song` (Data), `prev`, `next`.

- **Singly Linked List**:
  - **Playlist (`PlaylistNode`)**: Menyimpan daftar playlist. Setiap node berisi nama playlist dan pointer ke `head` dari daftar lagu di dalamnya.
  - **Isi Playlist (`PlaylistItemNode`)**: Linked list di dalam setiap Playlist yang menyimpan pointer ke lagu (`SongNode*`) yang ada di *main library*. Ini menghemat memori karena tidak menduplikasi data lagu.

- **Queue (Antrean)**:
  - Digunakan untuk fitur antrean lagu (`PlayerEngine::enqueue`).
  - Menggunakan prinsip **FIFO (First In First Out)**: Lagu yang pertama masuk antrean akan diputar lebih dulu saat `nextSong()` dipanggil.
  - *Struct*: `QueueNode` (front, rear).

- **Stack (Tumpukan)**:
  - Digunakan untuk fitur Riwayat Putar (`PlayerEngine::history`).
  - Menggunakan prinsip **LIFO (Last In First Out)**: Lagu yang terakhir diputar berada di puncak tumpukan, memungkinkan fitur "Previous Song" untuk kembali ke lagu yang baru saja didengar.
  - *Struct*: `StackNode` (top).

## 3. Kendala dan Solusi

Selama pengembangan, ditemukan beberapa kendala teknis dan desain interaksi (UX) yang telah diselesaikan:

1.  **Redundansi Informasi "Sedang Memutar"**
    - **Kendala**: Pesan konfirmasi "SEDANG MEMUTAR" muncul setiap kali memilih lagu, lalu menumpuk dengan header menu utama, membuat tampilan berantakan (spam).
    - **Solusi**: Menghapus pesan konfirmasi instan setelah pemilihan lagu dan sepenuhnya mengandalkan header menu utama yang secara persisten menampilkan status lagu aktif. Ini membuat antarmuka lebih bersih.

2.  **Fleksibilitas Pemilihan Lagu**
    - **Kendala**: Menu "Putar Lagu" awalnya terlalu kaku atau berubah-ubah antara hanya ID atau hanya Judul.
    - **Solusi**: Mengembalikan menu "Putar Lagu" menjadi submenu yang memberikan opsi jelas kepada pengguna: "1. Berdasarkan ID" atau "2. Berdasarkan Judul", memberikan fleksibilitas maksimal.

3.  **Pencarian Lagu yang Sensitif Huruf (Case-Sensitivity)**
    - **Kendala**: Pengguna kesulitan mencari lagu jika tidak mengetikkan huruf kapital dengan tepat (misal: "pop" tidak menemukan "Pop").
    - **Solusi**: Mengimplementasikan fungsi `toLowerCase` di `Utils.cpp` untuk menstandarisasi input pengguna dan data lagu saat pencarian, sehingga pencarian menjadi tidak sensitif huruf besar/kecil (*case-insensitive*).

4.  **Logika Auto-Play yang Kompleks**
    - **Kendala**: Menentukan lagu apa yang harus diputar setelah lagu saat ini selesai (apakah lanjut ke lagu berikutnya di library, atau di playlist?).
    - **Solusi**: Mengimplementasikan variabel `playMode` (0 untuk Library, 1 untuk Playlist). Logika `nextSong()` mengecek mode ini. Jika Library, ia mencari node berikutnya dengan *Genre* yang sama. Jika Playlist, ia maju ke node berikutnya dalam linked list playlist tersebut.

5.  **Manajemen ID Lagu (Auto-Increment)**
    - **Kendala**: Menginput ID lagu secara manual saat menambah lagu baru rentan terjadi duplikasi atau konflik ID, serta merepotkan admin untuk mengingat ID terakhir.
    - **Solusi**: Mengimplementasikan sistem **Auto-Increment ID**. Fungsi `generateNewId()` akan memindai seluruh *Linked List* lagu untuk mencari ID terbesar yang ada saat ini, lalu menambahkan 1 untuk ID lagu baru. Ini menjamin setiap lagu baru selalu memiliki ID unik secara otomatis tanpa intervensi manual.

## 4. Rencana Pengembangan Masa Depan

Berikut adalah fitur prioritas yang direncanakan untuk pengembangan tahap selanjutnya:

1.  **Fitur Sorting (Pengurutan)**
    - Sistem saat ini hanya menampilkan lagu berdasarkan urutan masuk (ID). Pengembangan selanjutnya akan menambahkan opsi bagi User untuk mengurutkan daftar lagu di library berdasarkan **Judul (A-Z)**, **Artis**, atau **Tahun Rilis**. Ini akan mengimplementasikan algoritma sorting (seperti Merge Sort) pada struktur data Linked List.

2.  **Lagu Sering Diputar (Most Played)**
    - Menambahkan fitur pelacakan statistik lagu. Setiap kali lagu diputar selesai, *counter* `playCount` pada data lagu akan bertambah. Fitur ini akan memungkinkan User untuk melihat daftar "Top 10 Lagu Sering Diputar" atau membuat playlist otomatis berisi lagu-lagu favorit mereka berdasarkan frekuensi pemutaran.