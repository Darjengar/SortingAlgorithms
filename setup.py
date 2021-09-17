from distutils.core import setup, Extension

def main():
    setup(name="sorting",
          version="1.0.0",
          description="Sorting package",
          include_dirs=["/usr/include/python3.8"],
          ext_modules=[Extension("sorting", ["src/c/_sorting.c"])])

if __name__ == "__main__":
    main()