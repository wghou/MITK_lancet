/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/


#ifndef MITKPlanarFigureSOURCE_H_HEADER_INCLUDED
#define MITKPlanarFigureSOURCE_H_HEADER_INCLUDED

#include "mitkPlanarFigure.h"
#include "PlanarFigureExports.h"
#include "mitkCommon.h"
#include "mitkBaseProcess.h"

namespace mitk
{
/**
 * @brief Base class for all filters which have an object of type
 * mitk::PlanarFigure as output
 *
 * Base class for all filters which have an object of type mitk::PlanarFigure
 * as output. mitk::PlanarFigureSources do not provide support
 * for streaming, that is, that the requested region is always the largest
 * possible region.
 * @ingroup Process
 */
class PlanarFigure_EXPORT PlanarFigureSource : public mitk::BaseProcess
{
public:
    mitkClassMacro( PlanarFigureSource, BaseProcess );
    itkNewMacro( Self );

    typedef mitk::PlanarFigure OutputType;
    typedef OutputType::Pointer OutputTypePointer;
    typedef itk::DataObject::Pointer DataObjectPointer;

    /**
     * Allocates a new output object and returns it. Currently the
     * index idx is not evaluated.
     * @param idx the index of the output for which an object should be created
     * @returns the new object
     */
    virtual itk::DataObject::Pointer MakeOutput ( DataObjectPointerArraySizeType idx );

    /**
     * This is a default implementation to make sure we have something.
     * Once all the subclasses of ProcessObject provide an appopriate
     * MakeOutput(), then ProcessObject::MakeOutput() can be made pure
     * virtual.
     */
    virtual itk::DataObject::Pointer MakeOutput(const DataObjectIdentifierType &name);

    /**
     * Generates the input requested region simply by calling the equivalent
     * method of the superclass.
     */
    void GenerateInputRequestedRegion();

    /**
     * Graft output 0 to the parameter graft
     */
    virtual void GraftOutput(itk::DataObject *graft);
    /**
    * Graft output idx to the parameter graft
    */
    virtual void GraftNthOutput(unsigned int idx, itk::DataObject *graft);

    PlanarFigure* GetOutput(const DataObjectIdentifierType & key);
    const PlanarFigure* GetOutput(const DataObjectIdentifierType & key) const;
    PlanarFigure* GetOutput(DataObjectPointerArraySizeType idx);
    const PlanarFigure* GetOutput(DataObjectPointerArraySizeType idx) const;

protected:
    PlanarFigureSource();
    virtual ~PlanarFigureSource();
};
} // namespace mitk
#endif
