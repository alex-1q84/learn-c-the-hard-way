#lang racket/base
(require racket/runtime-path
         racket/file
         racket/string
         threading)

(define builds
  (string-join
   (~>> (directory-list ".")
        (map path->string)
        (filter (lambda (s) (string-suffix? s ".c")))
        (map (lambda (s) (string-trim s ".c" #:right? #t))))
   "\n"))

(define setting-parts (string-split (file->string ".gitignore") "#project builds"))

(define new-settings (string-join (list (car setting-parts) builds) "#project builds\n"))

(display-to-file new-settings ".gitignore" #:exists 'truncate)