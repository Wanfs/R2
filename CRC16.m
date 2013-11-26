Q = [255 100 50 101 105]; % Data
P = 0;
A = 0;
Xh = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1]; % X^16

if mod(length(Q),2) ~= 0
    Qtemp = [0 Q(1:end)]; % Append 0x00.
else
    Qtemp = Q(1:end);
end

for i= 1:2:length(Qtemp)
    Qi = double(de2bi(typecast(uint8([Qtemp(i+1) Qtemp(i)]), 'uint16')));
    A = gfadd(P, Qi); % P + Qi
    AXh = gfconv(A,Xh); % A*X^h
    [q,P] = gfdeconv(AXh,M); % Rem of AXh/M
end
dec2hex(bi2de(P))

