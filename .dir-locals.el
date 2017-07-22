;; Assume a makefile is present at project root and that dir-locals
;; (this file) is also at project root. Find the project root through
;; dir-locals and set the compile command. The project can now be
;; compiled from any project buffer.

((nil . ((eval . (let ((root-path (file-name-directory
				   (let ((d (dir-locals-find-file ".")))
				     (if (stringp d) d (car d))))))
		   (set (make-local-variable 'compile-command)
			;; cmake -H. -Bbuild && make -C build/ >/dev/null && ./run_tests
			;; (concat "cmake -H" root-path
			;; 	" -B" root-path "build"
			;; 	" && make -C " root-path "build/ >/dev/null"
			;; 	" && " root-path "run_tests")
			(concat root-path "run all")
			))))))
