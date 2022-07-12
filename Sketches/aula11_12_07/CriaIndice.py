import struct
import hashlib
import os

hashSize = 900001
fileName = "data/cep.dat"
indexName = "data/cep-hash.dat"
dataFormat = "72s72s72s72s2s8s2s"
indexFormat = "8sLL"
keyColumnIndex = 5

dataStruct = struct.Struct(dataFormat)
indexStruct = struct.Struct(indexFormat)


def h(key):
    return int(hashlib.sha1(key).hexdigest(),16)%hashSize

# Abre o arquivo para preencher em "branco"

fi = open(indexName,"wb")
emptyIndexRecord = indexStruct.pack(b"",0,0)
for i in range(0,hashSize):
    fi.write(emptyIndexRecord)
fi.close()

# Fim da escrita em default

# Arquivo em leitura
f = open(fileName,"rb")
# Arquivo em leitura e escrita sem truncar
fi = open(indexName,"r+b")

# Pega o tamanho do arquivo
fi.seek(0,os.SEEK_END)
fileIndexSize = fi.tell()

# Counter de conteudos escrito nos indices
recordNumber = 0

while True:
    line = f.read(dataStruct.size)

    if len(line) == 0: # EOF
        break
	# Pega o struct
    record = dataStruct.unpack(line)
	# Pega o CEP
    key = record[keyColumnIndex]
	# Calcula a chave
    p = h(key)

    fi.seek(p*indexStruct.size,os.SEEK_SET)
    indexRecord = indexStruct.unpack(fi.read(indexStruct.size))
    fi.seek(p*indexStruct.size,os.SEEK_SET)

	# Verifica se a chave já possiu algum ocupante
    if indexRecord[0][0] == b"\0":
        fi.write(indexStruct.pack(key,recordNumber,0))
    else:
		# Guarda em um ponteiro 
        nextPointer = indexRecord[2]
		# Add à chave atual o endereço do último == elemento a ser adicionado
        fi.write(indexStruct.pack(indexRecord[0],indexRecord[1],fileIndexSize))
		# Reposiciona o arquivo para escrever o novo arquivo
        fi.seek(0,os.SEEK_END)
		# Escreve o novo valor referenciado no final do arquivo
        fi.write(indexStruct.pack(key,recordNumber,nextPointer))
		# Descobre qual o NOVO ultimo local para add o proximo elemento colidido
        fileIndexSize = fi.tell()
    recordNumber += 1
f.close()
fi.close()
