// Copyright Epic Games, Inc. All Rights Reserved.

//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 4.0.1
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class FDatasmithFacadeLevelVariantSets : FDatasmithFacadeElement {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal FDatasmithFacadeLevelVariantSets(global::System.IntPtr cPtr, bool cMemoryOwn) : base(DatasmithFacadeCSharpPINVOKE.FDatasmithFacadeLevelVariantSets_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(FDatasmithFacadeLevelVariantSets obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  protected override void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          DatasmithFacadeCSharpPINVOKE.delete_FDatasmithFacadeLevelVariantSets(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      base.Dispose(disposing);
    }
  }

  public FDatasmithFacadeLevelVariantSets(string InElementName) : this(DatasmithFacadeCSharpPINVOKE.new_FDatasmithFacadeLevelVariantSets(InElementName), true) {
  }

  public void AddVariantSet(FDatasmithFacadeVariantSet InVariantSetPtr) {
    DatasmithFacadeCSharpPINVOKE.FDatasmithFacadeLevelVariantSets_AddVariantSet(swigCPtr, FDatasmithFacadeVariantSet.getCPtr(InVariantSetPtr));
  }

  public int GetVariantSetsCount() {
    int ret = DatasmithFacadeCSharpPINVOKE.FDatasmithFacadeLevelVariantSets_GetVariantSetsCount(swigCPtr);
    return ret;
  }

  public FDatasmithFacadeVariantSet GetVariantSet(int VariantSetIndex) {
	global::System.IntPtr objectPtr = DatasmithFacadeCSharpPINVOKE.FDatasmithFacadeLevelVariantSets_GetVariantSet(swigCPtr, VariantSetIndex);
	if(objectPtr == global::System.IntPtr.Zero)
	{
		return null;
	}
	else
	{
		return new FDatasmithFacadeVariantSet(objectPtr, true);
	}
}

  public void RemoveVariantSet(FDatasmithFacadeVariantSet InVariantSetPtr) {
    DatasmithFacadeCSharpPINVOKE.FDatasmithFacadeLevelVariantSets_RemoveVariantSet(swigCPtr, FDatasmithFacadeVariantSet.getCPtr(InVariantSetPtr));
  }

}
