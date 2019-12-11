m = 10; % sub-seq size

 n = [10, 50, 100, 200, 300, 500, 800, 1000, 1250, 1500, 2000, 2500, 3000, 4000]; % total seq size
 t_naive = [0.01 0.06 0.23 0.882 1.94 5.20 13.22 20.63 31.89 45.54 80.31 124.82 182.29 326.17]; % Naive function execution time
 t_sort = [0.009 0.0346 0.09 0.289 0.488 0.93 1.69 2.298 3 3.816 5.53 7.34 9.23 13.20]; % Sort function execution time
 
hold on;
xlabel('Nombre de particules (n)');
ylabel('Temps d''exécution (s)');
plot(n, t_naive, '-');
plot(n, t_sort, '-');
legend('naïf (brute force)', 'Barnes-Hut');