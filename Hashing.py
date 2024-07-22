# -*- coding: utf-8 -*-
"""Untitled29.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1h0y5UfMqXGjCKEujPvNLv69Ij42FkDvb
"""

import re
from typing import List, Optional
import math
import random
from collections import defaultdict
import matplotlib.pyplot as plt


class Node :
    def __init__(self, key: str, value: int):
      self.key = key
      self.value = value
      self.next = None

class HashTable:
    def __init__(self, max_hash: int):
        self.max_hash = max_hash
        self.table = [None] * max_hash

    # def hash_function(self, key: str) -> int:
    #     return sum(ord(c) for c in key) % self.max_hash

    # hash(s) = s[0]*p^0 + s[1]*p^1 +
    def hash_function(self, key: str) -> int:
        p = 31
        m = self.max_hash
        hash_value = 0
        p_pow = 1

        for char in key:
            hash_value = (hash_value + (ord(char) - ord('a') + 1) * p_pow) % m
            p_pow = (p_pow%m * p%m) % m

        return hash_value


    def find(self, key: str) -> Optional[int]:
        idx = self.hash_function(key)
        current = self.table[idx]
        while current is not None:
            if current.key == key:
                return current.value
            current = current.next
        return None

    def insert(self,key:str,value:int) -> None:
        idx = self.hash_function(key)
        if self.table[idx] is None:
            self.table[idx] = Node(key, value)
        else:
            current = self.table[idx]
            while current.next is not None and current.key != key:
                current = current.next
            if current.key == key:
                current.value = value
            else:
                current.next = Node(key, value)

    def increase(self, key: str) -> None:
        idx = self.hash_function(key)
        current = self.table[idx]
        while current is not None:
            if current.key == key:
                current.value += 1
                return
            current = current.next
        self.insert(key, 1)

    def list_all_keys(self) -> List[str]:
        keys = []
        for head in self.table:
            current = head
            while current is not None:
                keys.append(current.key)
                current = current.next
        return keys

    def list_all_keys_with_counts(self) -> List[tuple]:
        keys_with_counts = []
        for head in self.table:
            current = head
            while current is not None:
                keys_with_counts.append((current.key, current.value))
                current = current.next
        return keys_with_counts

    def calculate_histogram_and_variance(self):
        lengths = [0] * self.max_hash
        for i, head in enumerate(self.table):
            current = head
            while current is not None:
                lengths[i] += 1
                current = current.next

        avg_length = sum(lengths) / self.max_hash
        variance = sum((x - avg_length) ** 2 for x in lengths) / self.max_hash

        print(f"Average List Length: {avg_length}")
        print(f"Variance: {variance}")

        temp = sorted(lengths)
        temp.sort(reverse = True)
        topPercentage = self.max_hash//10
        print(temp[:topPercentage])


        plt.bar(range(len(lengths)), lengths, color='blue')
        plt.xlabel('Index')
        plt.ylabel('Length')
        plt.title('Bar Chart of Collision List Lengths')
        plt.show()


    def output_to_file(self, filename: str) -> None:
        with open(filename, 'w') as f:
            for key, value in self.list_all_keys_with_counts():
                f.write(f"{key}: {value}\n")


def process_text(text: str) -> List[str]:
    return re.findall(r'\b\w+\b', text.lower())

def main():
    max_hash_values = [30, 300, 1000]
    with open('alice_in_wonderland.txt','r',encoding = 'utf-8') as file:
        text = file.read()

    words = process_text(text)
    for max_hash in max_hash_values:
        print(f"Processing with MAXHASH = {max_hash}")
        hash_table = HashTable(max_hash)

        for word in words:
            if hash_table.find(word) is not None:
                hash_table.increase(word)
            else:
                hash_table.insert(word, 1)


        wordToBeInserted = "JenishKothari"

        if(hash_table.find(wordToBeInserted)):
          print("Word Found")
        else:
          print("Word not found")
          hash_table.insert(wordToBeInserted,1)

        print(hash_table.list_all_keys())

        hash_table.output_to_file(f'output_{max_hash}.txt')
        hash_table.calculate_histogram_and_variance()
        print("\n")

if __name__ == "__main__":
    main()
